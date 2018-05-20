#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <complex>


using namespace std;
//create global size N

void find_C(int N, float x[], float y[],float Cx[],float Cy[],int m,float rs)
{
	float lcmX = 0, lcmY = 0;
  float tempx[N] , tempy[N];
  float temp;
  int count , min , flag;

  std::cout<<"entered find_C"<<endl;
  for(int i=0;i<N;i++){
    tempx[i] = x[i];
    tempy[i] = y[i];
  }
  
  //Loops taking too long due to big N, why not just find center if an agent is within
  //20m of the A[i]....................................
  for(int i=0;i<N;i++){
    //min =  (i+1)%N;  //when i=N-1 we'll get 0 :P
    flag = 0;
    count = 0;
    lcmX = 0;
    lcmY = 0;
    for(int j=0;j<N;j++){
      min = j;
      //flag = 0;
      std::cout<<"j "<<j<<endl;
      if(i != j){
        for(int k=j+1;k<N;k++){  
          if(i!=k && std::sqrt(std::pow(tempx[i] - tempx[k],2) + std::pow(tempy[i] - tempy[k],2)) < 
              std::sqrt(std::pow(tempx[i] - tempx[min],2) + std::pow(tempy[i] - tempy[min],2))){
            min = k;
            std::cout<<"k "<<k<<endl;
          }   
        }
        temp = tempx[min];
        tempx[min] = tempx[j];
        tempx[j] = temp;

        temp = tempy[min];
        tempy[min] = tempy[j];
        tempy[j] = temp;

        //count++;
        /*std::cout<<"count in find_C "<<count<<endl;
        if(count > m){
          flag = 1;
          break;
        }
        
      }
      /*if(flag == 1)
        break;*/
      }
    }
  
/*  for(int j=0;j<N;j++){
    if(i!=j && std::sqrt(std::pow(x[i] - x[j],2) + std::pow(y[i] - y[j],2)) < 10.0){
      lcmX = lcmX + tempx[i];
      lcmY = lcmY + tempy[i];      
    }
  }
*/
	for(int j=0;j<m;j++){  //EARLIER YOU HAD i hear and in the outer loop too 
		lcmX = lcmX + tempx[i];
		lcmY = lcmY + tempy[i];
	}
	lcmX = lcmX/m;
	lcmY = lcmY/m;

	for(int j=0;j<m;j++){
		Cx[i] = lcmX - x[i]/std::abs(lcmX - x[i]);
		Cy[i] = lcmY - y[i]/std::abs(lcmY - x[i]);
	}
  }
}

void find_Ra(float Rax[],float Ray[] , float x[], float y[],int N,float ra,float rhoa)
{
	float dist;
	for(int i=0;i<N;i++){
		//std::cout<<"value of Ra before changing, must be 0: "<<Rax[i]<<" "<<Ray[i]<<endl;
		for(int j=0;j<N;j++){
			if(j != i){
				dist = std::sqrt(std::pow(x[i] - x[j],2) + std::pow(y[i] - y[j],2));
				if(dist < ra ){
					Rax[i] = Rax[i] + (x[i] - x[j])/std::abs(x[i] - x[j]); //we need norm here
					Ray[i] = Ray[i] + (y[i] - y[j])/std::abs(y[i] - y[j]);
					//Rax[i] = rhoa*Rax[i];
					//Ray[i] = rhoa*Ray[i];
					//std::cout<<"in find_Ra : "<<Rax[i]<<" "<<Ray[i]<<endl<<"dist: "<<dist<<endl;
				}
				else{
					//std::cout<<"dist greatert thn 2 "<<dist;
				}
			}
		}
	}
}

void angular_noise_effect(float Ex[],float Ey[],float x[],float y[],int N,float p,float e)
{
	float rand_no;

	//srand (time(NULL));

	for(int i=0;i<N;i++){
		rand_no = rand()%100;
		rand_no = rand_no/100.0;
		std::cout<<i<<" randno. "<<" "<<rand_no<<endl;
		if(p >= rand_no){
			x[i] = x[i] + e*(rand()%2-1);
			y[i] = y[i] + e*(rand()%2-1);
		}
	}
}

void steps_per_timestep(float cur_ptx[] , float cur_pty[] , float x[] , float y[] ,float steps, int N)
{
	float diffX[N] , diffY[N];
	float norm[N] ,normy;
	float unitvecx,unitvecy;
	float step;

	for(int i=0;i<N;i++){
		diffX[i] = cur_ptx[i] - x[i];
		diffY[i] = cur_pty[i] - y[i];
	}
	for(int i=0;i<N;i++){
		norm[i] = std::sqrt(std::pow(diffX[i],2) + std::pow(diffY[i],2));
		//std::cout<<"norm "<<i<<" "<<norm[i]<<endl;
	}
	//normy = std::norm(diffY);
	for(int i=0;i<N;i++){
		step = steps;
		if(norm[i] < steps)
			step = norm[i];

		if(norm[i] == 0 ){
			unitvecx = 0;
			unitvecy = 0;
		}else{
			unitvecx = diffX[i]/norm[i];
			unitvecy = diffY[i]/norm[i];
		}
		cur_ptx[i] = cur_ptx[i] + unitvecx*step;
		cur_pty[i] = cur_pty[i] + unitvecy*step;
		x[i] = cur_ptx[i];
		y[i] = cur_pty[i];
	}
}

void find_Rs(float Rsx[] , float Rsy[],float sx,float sy , float x[], float y[],int N,float rs,float rhos)
{
  for(int i=0;i<N;i++){
    if(std::sqrt(std::pow(x[i] - sx,2) + std::pow(y[i] - sy,2)) < rs){
      Rsx[i] = (x[i] - sx)/std::abs(x[i] - sx);
      Rsy[i] = (y[i] - sy)/std::abs(y[i] - sy);
    }
  }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "shepherd");
  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_marker_shepherd", 1);
  //ros::Publisher marker_pub2 = n.advertise<visualization_msgs::Marker>("visualization_marker2", 1);

  //RANDOMIZING RANDOM:
  srand (time(NULL));

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  int N = 1000; //o. of random no.s

  int mark;

  float x[N] , y[N] , ini_x[N] , ini_y[N];
  float sx,sy; //pos of sheperd
  float Cx[N], Cy[N] , Rax[N], Ray[N] , Rsx[N] , Rsy[N] , Ex[N] , Ey[N];
  float cur_pty[N] , cur_ptx[N];

  visualization_msgs::MarkerArray M;
  M.markers.resize(N + 1);

  for(int i=0;i<N;i++){  	
  	x[i] = rand()%100 - 50 ;
  }
  
  for(int i=0;i<N;i++) 
  	y[i] = rand()%100 - 50 ;

  for(int i=0;i<N;i++){
  	if(i!=0){
  		mark = 0;
  		for(int j=0;j<i-1;j++){
  			if(i!=j && (x[j] == x[i] && y[j] == y[i]))
  			mark = j;
  		}
  	}
  	while(i!=0 && x[mark] == x[i] && y[mark] == y[i]){
	  	x[i] = rand()%100 - 50 ; 
  		y[i] = rand()%100 - 50 ;
  	}

  	 ini_y[i] = y[i];
  	 ini_x[i] = x[i];
  	 Rax[i] = 0;
  	 Ray[i] = 0;

    M.markers[i].header.frame_id = "/my_shepherd";
    M.markers[i].header.stamp = ros::Time::now();
      
    M.markers[i].ns = "shepherd";
      
    M.markers[i].id = i;
      
    M.markers[i].type = shape;
      
    M.markers[i].action = visualization_msgs::Marker::ADD;

    M.markers[i].pose.position.x = x[i];
    M.markers[i].pose.position.y = y[i];

    M.markers[i].pose.position.z = 0;

    M.markers[i].pose.orientation.x = 0.0;
    M.markers[i].pose.orientation.y = 0.0;
    M.markers[i].pose.orientation.z = 0.0;
    M.markers[i].pose.orientation.w = 1.0;
      
    M.markers[i].scale.x = 0.6;
    M.markers[i].scale.y = 0.6;
    M.markers[i].scale.z = 0.6;
      
    M.markers[i].color.r = 0.0f;
    M.markers[i].color.g = 1.0f;
    M.markers[i].color.b = 0.0f;
    M.markers[i].color.a = 1.0;
 
    M.markers[i].lifetime = ros::Duration();

  }

// MARKER FOR SHEPHERD : LAST ELEMENT OF MATRIX : 

    M.markers[N].header.frame_id = "/my_shepherd";
    M.markers[N].header.stamp = ros::Time::now();
      
    M.markers[N].ns = "shepherd";
      
    M.markers[N].id = N;
      
    M.markers[N].type = shape;
      
    M.markers[N].action = visualization_msgs::Marker::ADD;

    M.markers[N].pose.position.x =  0.0;
    M.markers[N].pose.position.y = -50.0;

    M.markers[N].pose.position.z = 0;

    M.markers[N].pose.orientation.x = 0.0;
    M.markers[N].pose.orientation.y = 0.0;
    M.markers[N].pose.orientation.z = 0.0;
    M.markers[N].pose.orientation.w = 1.0;
      
    M.markers[N].scale.x = 0.6;
    M.markers[N].scale.y = 0.6;
    M.markers[N].scale.z = 0.6;
      
    M.markers[N].color.r = 1.0f;
    M.markers[N].color.g = 0.0f;
    M.markers[N].color.b = 0.0f;
    M.markers[N].color.a = 1.0;
 
    M.markers[N].lifetime = ros::Duration();



  	//ros::Duration(5);
  	
  //float forward = 0.5;
	float e=0.3; // strength of error movement
	float p=0.05; // probability of an error
	//Xstartpos=0 #swarm initial position
	//Ystartpos=0
	//N=50# number of agents
	float dps=0.5; // speed of agents
	float ra =2.0 ; // distance for self repulsion
	float rhoa=2.0; // strength of self repulsion 
	float c = 1.05;
	float rhos = 1;
	float d = 0.2;
  int m = std::ceil(0.9*N);
  float rs = 20.0; //radius of influence

  while(ros::ok())
  {
  	//marker_pub.publish(M);

  	std::cout<<"yolo"<<endl;

  	/*std::cout<<"Before calling functions:"<<endl;
  	for(int i=0;i<N;i++){
  		std::cout<<"ini_x "<<x[i]<<"  ini_y "<<y[i]<<endl;
  	}*/
  	
  	//std::cout<<"x "<<x[0]<<"  y "<<y[0]<<endl;
  	//Now we need to find Ci ,Ria,Ris
  	find_C(N,x,y,Cx,Cy,m,rs); 
    std::cout<<"find_C check"<<endl;
  	find_Ra(Rax,Ray,x,y,N,ra,rhoa);
    std::cout<<"find_Ra check"<<endl;
  	find_Rs(Rsx,Rsy,sx,sy,x,y,N,rs,rhos);
    std::cout<<"find_Rs check"<<endl;
  	//angular_noise_effect(Ex,Ey,x,y,N,p,e);
  	for(int i=0;i<N;i++){
  		std::cout<<"x and y "<<x[i]<<" "<<y[i]<<endl;  
  		cur_ptx[i] = x[i] + rhoa*Rax[i] + c*Cx[i] + rhos*Rsx[i]; // NOT ADDED THE CONSTANTS
  		cur_pty[i] = y[i] + rhoa*Ray[i] + c*Cy[i] + rhos*Rsy[i]; 
  	}
  	steps_per_timestep(cur_ptx,cur_pty,x,y,dps,N);

  	//due to the suze of the block if the new position of the block, if the new pos should have a distance of
  	//0.6 metres from others
  	//can_move_or_not(x,y,N); 

  	/*for(int i =0;i<10;i++){
  	//intent to see in phone	
  	std::cout<<i<<" x "<<x[i]<<"  y "<<y[i]<<"  Ra: "<<Rax[i]<<"  "<<Ray[i]<<endl;
  	}*/
  	/*std::cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
  	for(int i =0;i<N;i++){
  		std::cout<<"Cx "<<Cx[i]<<"  Cy "<<Cy[i]<<endl;
  	}*/
  	
    //std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

  	/*for(int i=0;i<N;i++){
  		std::cout<<i<<" "<<"Rax "<<Rax[i]<<" Ray "<<Ray[i]<<endl;
  	}*/

  	marker_pub.publish(M);
  	ros::Duration(0.1);

  	for(int i=0;i<N;i++){
  		M.markers[i].pose.position.x = x[i] ;
  		M.markers[i].pose.position.y = y[i] ;
  		//M.markers[i].pose.position.x = x[i] + dps;
  		
  		//x[i] = M.markers[i].pose.position.x;
  		//y[i] = M.markers[i].pose.position.y;

  		Rax[i] = 0;
  		Ray[i] = 0;
  		Cx[i] = 0;
  		Cy[i] = 0;
      Rsx[i] = 0;
      Rsy[i] = 0;
  		cur_ptx[i] = 0;
  		cur_pty[i] = 0;
  	}
  	//std::cout<<"pos of 1: "<<x[0]<<"  y: "<<y[0]<<endl;
  	//std::cout<<" Rax : "<<Rax[0]<<endl;

  	r.sleep();
  }

//return 0;
}  

	