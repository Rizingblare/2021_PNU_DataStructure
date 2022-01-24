#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
int n,k;

struct customer{
	int id;			//¾ÉÀº »ç¶÷
	int seat;		//ÁÂ¼® ¹øÈ£
};

struct seat{
	int id;			//¾ÉÀº »ç¶÷
	int number;		//ÁÂ¼® ¹øÈ£
	int gap;		//´ÙÀ½ ÁÂ¼® »çÀÌÀÇ ºóÄ­
};

vector<customer> cafe;	//Ãâ·Â list
list<seat> seat_list;	//ÇöÀç cafe¿¡ ÀÚ¸®

int already_in_cafe(int ID){
	//argument: »ç¶÷ÀÇ ID 
	//usage   : ID¿¡ ÇØ´çÇÏ´Â »ç¶÷ÀÌ ÇöÀç cafe¿¡ ÀÖ´ÂÁö È®ÀÎ
	//return  : ID¿¡ ÇØ´çÇÏ´Â »ç¶÷ÀÌ ¾ÉÀº ÁÂ¼®¹øÈ£ / cafe¿¡ ¾ø´Ù¸é 0
	
	int seat_number = 0;
	
	for(auto customer : seat_list){
		if(customer.id == ID){
			seat_number = customer.number;
			break;
		}
	}
	
	return seat_number;
}

void get_out(int seat_number){
	//argument: ÁÂ¼® ¹øÈ£
	//usage   : ÇØ´ç ÁÂ¼® ¹øÈ£¿¡ ¾ÉÀº »ç¶÷À» ÇöÀç cafe¿¡¼­ ³ª°¡°Ô ÇÔ
	//return  : void
	
	list<seat>::iterator it;
	
	for(auto i=seat_list.begin(); i!=seat_list.end(); i++){
		if(i->number == seat_number){
			it=i;
			break;
		}
	}
	int gap = it->gap;
	
	//Ã¹¹øÂ° ÀÚ¸®¿¡ ¾É¾ÆÀÖ´Ù¸é (1¹øÀÚ¸®°¡ ¾Æ´Ñ n¸íÁß Ã¹¹øÂ° ÀÚ¸®)
	if(it == seat_list.begin()){
		//¸Ç ¸¶Áö¸· ÀÚ¸®ÀÇ gapÀ» ¼öÁ¤.
		list<seat>::iterator it_last = --seat_list.end();
		it_last->gap = it_last->gap + gap + 1;
		seat_list.erase(it);
	}
	//i¹øÂ° ÀÚ¸®¿¡ ¾É¾Ò´Ù¸é
	else{
		//i-1¹øÂ° ÀÚ¸®ÀÇ gapÀ» ¼öÁ¤.
		it--;
		it->gap = it->gap + gap + 1;
		it++;
		seat_list.erase(it);
	}
	
}

int seat_in_cafe(int ID){
	//argument: »ç¶÷ÀÇ ID
	//usage   : ID¿¡ ÇØ´çÇÏ´Â »ç¶÷À» Á¶°Ç¿¡¸Â°Ô cafe¿¡ ¾ÉÈû
	//return  : »ç¶÷ÀÌ ¾ÉÀ» ÀÚ¸®°¡ ÀÖ´Ù¸é ¾ÉÀº ÁÂ¼® ¹øÈ£ / ¾ÉÀ» ÀÚ¸®°¡ ¾ø´Ù¸é 0 
	
	list<seat>::iterator it;
	seat new_seat = {ID,0,0};
	
	//cafe¿¡ ¾Æ¹«µµ ¾øÀ¸¸é
	if(seat_list.empty()){	
		it		 = seat_list.begin();
		new_seat = {ID,1,n-1};
	}
	else{
		//¾ÉÀ»ÀÚ¸® Å½»ö
		int max_gap = 0;
		
		for(auto i=seat_list.begin(); i!=seat_list.end(); i++){
			if(i->gap > max_gap){
				max_gap = i->gap;
				it 		= i;
			}
		}
		
		//ÀÚ¸®°¡ ¾ø´Ù¸é
		if(max_gap == 0)	return 0;
		
		//º¯°æÁ¡ ¼öÁ¤, »õ ÀÚ¸®¿¡ ´ëÇÑ º¯¼ö ±¸ÇÏ±â
		it->gap = (max_gap%2==0) ? (max_gap/2-1) : (max_gap/2);
		
		int gap    = (max_gap/2);
		int number = (it->number + it->gap)%n + 1;
		
		new_seat = {ID, number, gap};
	}
	
	//ÀÚ¸®¿¡ ¾ÉÈ÷±â
	//ÀÚ¸®°¡ ¸Ç¾ÕÀÚ¸®ÀÌ¸é
	if((it->number + it->gap)/n >= 1)	seat_list.insert(seat_list.begin(),new_seat); 
	else								seat_list.insert(++it,new_seat);
	
	return new_seat.number;
}

int main(){
	
	//ifstream cin("1.inp");   //test È®ÀÎ 
	
	cin >> n >> k;
	
	for(int i=0;i<k;i++){
		int ID;
		cin>>ID;
		
		int seat_number;
		
		//cafe¿¡ ÀÌ¹Ì ÀÖÀ¸¸é						//cafe¿¡¼­ ³ª°¡±â.
		if	   (seat_number = already_in_cafe(ID))	get_out(seat_number);
		//cafe¿¡ µé¾î °¬´Ù¸é                        //Ãâ·Â list¿¡ push.
		else if(seat_number = seat_in_cafe(ID))		cafe.push_back(customer{ID,seat_number});
	}
	
	//OUTPUT
	for(auto customer : cafe){
		cout << customer.id  << " ";
		cout << customer.seat<<"
";
	}
	
}