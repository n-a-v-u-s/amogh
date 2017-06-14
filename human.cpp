#include<string.h>
#include<math.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std; 

class Organ{

    public:
    int health;
    int healthrem(){    
	return health;
    }
		
};

class ear:public Organ{
    public:
    ear(int t){
      health=t;
    }
    int hear(){
	 if(health>0)
	    return 1;
	 else
            return 0;
    }
};
class eye:public Organ{
    public:
    eye(int t){
      health=t;
    }
    int see(){
	if(health>0)
	  return 1;
	else
	  return 0;
    }
};
class leg:public Organ{
    public:
    leg(int t){
      health=t;
    }
};
    
class Human{
    public:
    char name[30];  
    int x,food,med,dis,health,pred,humhealth;
    int fdspwn,medspwn,predspwn;
    ear e[2]={{15},{15}};
    eye y[2]={{15},{15}};
    leg l[2]={{20},{20}};
    Human(){
	predspwn=0;
    fdspwn=0;
    medspwn=0;
	health=100;
	x=0;	
	food=20;
	med=0;
	dis=0;
    }
    void move(){
	if(food>0&&(l[0].health||l[1].health)>0){    //He can move with one leg
	  x++;
	  food=food-1;
	  ofstream f;
	  f.open("distance.txt",ios::app);
	  f<<" "<<x;
	  f.close();
    
	}
    }    
    
    void disease(){
	if(dis==0){
	 if(rand()%10<2){
              dis=1;
	      switch (rand()%3){
		case 0:		
		strcpy(name,"Gangrene");	//gangrene
		if(l[0].health)
		  l[0].health-=3;
		if(l[1].health)
		  l[1].health-=3;
		break;
		case 1:
		strcpy(name,"Alzheimers");	//Alzheimers
		if(e[0].health)
		  e[0].health-=3;
		if(e[1].health)
		  e[1].health-=3;	
		if(y[0].health)
		  y[0].health-=3;
		if(y[1].health)
		  y[1].health-=3;
		break;
		case 2:
		strcpy(name,"Deafness");	//deafness
		if(food)
		  food-=1;

	      }
	  }
	  		
       }
       else{
		   if(med==1){
	 	    dis=0;
		    strcpy(name,"");
		    med=0;
		   }
		   else{

		      if(strcmp(name,"Gangrene")==0){
			     if(l[0].health)
		  		l[0].health-=3;
		       	     if(l[1].health)
		  		l[1].health-=3;
		      }		                	  
		      else if(strcmp(name,"Alzheimers")==0){
			     if(e[0].health)
				  e[0].health-=3;
			     if(e[1].health)
			          e[1].health-=3;	
			     if(y[0].health)
			          y[0].health-=3;
			     if(y[1].health)
			          y[1].health-=3;
        	      }
		      else if(strcmp(name,"Deafness")==0){
			     if(food>0)
			       food-=1;	
		      }
				
		   }
        }		
     }
     void predescape(){
        if(e[0].hear()>0||e[1].hear()>0)
           ;
        else if(pred==1)
           if(rand()%2)
	         humhealth=0;
	pred=1;
        
     }	
     int Humanstats(){
        humhealth=(e[0].health+abs(e[0].health)+e[1].health+abs(e[1].health)+y[0].health+abs(y[0].health)+y[1].health+abs(y[1].health)+l[0].health+abs(l[0].health)+l[1].health+abs(l[1].health))/2;
	move();
	cout<<" health"<<humhealth<<" Food"<<food<<" Disease"<<name<<endl;
	return humhealth;
     }    
     void correction(){
	
		if(medspwn==1){
		   if((y[0].health>0||y[1].health>0)&&med==0)
			  med=1;
		}
		if(fdspwn==1){
		   if(y[0].see()>0||y[1].see())
			  food+=1;
		  
		}
    }	
    int living(){
		correction();
		move();
	 	
	        predescape();
		if(humhealth==0){
	                 cout<<"  predator caught you are "; 
                         return 0;
                }
		else{
	  	         disease();
			 pred=0; 
                         return Humanstats();
		}
    }	
};


class Environment{
     
     int predator;  
     public:
     Environment(){
	 predator=0;
     }
     int fdspawn(){
	if(rand()%10<2)
	   return 1;
	else
	   return 0;	
     }	
     int predspawn(){
	if((rand()%10)<4)
	   return 1;
	else
           return 0;     
     }
   
     int medspawn(){
	if(rand()%20<5)
           return 1;
	else
      	   return 0;
     }
     void calling(Human &a){
	if(fdspawn())
	   a.fdspwn=1;
        else
	   a.fdspwn=0;
	
	if(predspawn())
	   a.pred=1;
        else	
	   a.pred=0;
						
	if(medspawn())
	   a.medspwn=1;
	else
       	   a.medspwn=0;
     }
     
     
};
	   
int main(){
	int i;
	Human a;
	Environment s;
	srand(time(0));
	s.calling(a);
	i=a.living();
	
			
	while(i>0){
		   s.calling(a);
	       	   i=a.living();		
		   if(i<=0){
		      cout<<" dead\n";
		      ofstream f;
		      f.open("distance.txt",ios::app);
		      f<<"end\n";
		      f.close();
		      break;
		   }
	}
        return 0;
}

