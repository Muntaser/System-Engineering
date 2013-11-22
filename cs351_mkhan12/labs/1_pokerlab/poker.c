#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "poker.h"

/* converts a hand (of 5 cards) to a string representation, and stores it in the
 * provided buffer. The buffer is assumed to be large enough.
 */
int counter;

void hand_to_string (hand_t hand, char *handstr) {
    char *p = handstr;
    int i;
    char *val, *suit;
    for (i=0; i<5; i++) {
        if (hand[i].value < 10) {
            *p++ = hand[i].value + '0';
        } else {
            switch(hand[i].value) {
            case 10: *p++ = 'T'; break;
            case 11: *p++ = 'J'; break;
            case 12: *p++ = 'Q'; break;
            case 13: *p++ = 'K'; break;
            case 14: *p++ = 'A'; break;
            }
        }
        switch(hand[i].suit) {
        case DIAMOND: *p++ = 'D'; break;
        case CLUB: *p++ = 'C'; break;
        case HEART: *p++ = 'H'; break;
        case SPADE: *p++ = 'S'; break;
        }
        if (i<=3) *p++ = ' ';
    }
    *p = '\0';
}

/* converts a string representation of a hand into 5 separate card structs. The
 * given array of cards is populated with the card values.
 */
void string_to_hand (const char *handstr, hand_t hand) {
    const char *q = handstr;
    int i;
    
    for (i=0; i<5; i++) {
        if (isdigit(*q)) {
            hand[i].value=atoi(q++);
        } else {
            switch(*q++) {
            case 'T': hand[i].value=10; break;
            case 'J': hand[i].value=11; break;
            case 'K': hand[i].value=12; break;
            case 'Q': hand[i].value=13; break;
            case 'A': hand[i].value=14; break;
            }
        }
        switch(*q++) {
        case 'D': hand[i].suit=DIAMOND; break;
        case 'C': hand[i].suit=CLUB; break;
        case 'H': hand[i].suit=HEART; break;
        case 'S': hand[i].suit=SPADE; break;
        }
        *q++;
    }
    


}

/* sorts the hands so that the cards are in ascending order of value (two
 * lowest, ace highest */
void sort_hand (hand_t hand) {
int i,j;
hand_t h1= hand;
for(i=4;i>=0;i--){
for(j=0;j<=i;j++){
if(hand[j].value>hand[j+1].value){
card_t c=hand[j];
hand[j]=hand[j+1];
hand[j+1]=c;
}
}
}

}
int count_pairs (hand_t hand) {
hand_t h1=hand;
int i,pair,mark;
for(i=0;i<4;i++){
if(hand[i].value==hand[i+1].value ||hand[i].value==hand[i+2].value||hand[i].value==hand[i+3].value||hand[i].value==hand[i+4].value){
mark++;
}
}
return mark;


}

int is_onepair (hand_t hand) {
hand_t h2=hand;


if(count_pairs(hand)>=1)
return 1;
 return 0;

}

int is_twopairs (hand_t hand) {
hand_t h3=hand;
if(count_pairs(hand)==2)
return 1;
    return 0;
}

int is_threeofakind (hand_t hand) {

int i, j,mark,fkind;
if(hand[0].value==hand[1].value && hand[1].value==hand[2].value ){
fkind++;
return 1;
return 0;
}
else if(hand[0].value==hand[1].value && hand[1].value==hand[3].value ){fkind=1;
return 1;
return 0;}
else if(hand[0].value==hand[1].value && hand[1].value==hand[4].value){fkind=1;
return 1;
return 0;}
else if(hand[0].value==hand[2].value && hand[2].value==hand[3].value){
fkind=1;
return 1;
return 0;}
else if(hand[0].value==hand[2].value && hand[2].value==hand[4].value){
fkind=1;
return 1;
return 0;}
else if(hand[0].value==hand[3].value && hand[3].value==hand[4].value){
fkind=1;
return 1;
return 0;}
else if(hand[1].value==hand[2].value && hand[2].value==hand[3].value){
fkind=1;
return 1;return 0;}
else if(hand[1].value==hand[2].value && hand[2].value==hand[4].value){
fkind=1;
return 1;return 0;}
else if(hand[1].value==hand[3].value && hand[3].value==hand[4].value){
fkind=1;
return 1;return 0;}
else if(hand[2].value==hand[3].value && hand[3].value==hand[4].value){
fkind=1;
return 1;
return 0;}
else{
return 0;
}
}



int is_straight (hand_t hand) {
sort_hand(hand);


     if(hand[0].value==hand[1].value-1 && hand[0].value==hand[2].value-2 && hand[0].value==hand[3].value-3 && hand[0].value==hand[4].value-4){
return 1;
}
else if(hand[0].value==2 && hand[1].value==3 && hand[2].value==4 && hand[3].value==5 &&  hand[4].value==14){
return 1;
}
else{
       return 0;
}
    
    
}

int is_fullhouse (hand_t hand) {
sort_hand(hand);
if(hand[0].value==hand[1].value && hand[1].value !=hand[2].value){

if(hand[3].value==hand[4].value && hand[3].value==hand[2].value)
    return 1;
}
if(hand[0].value==hand[1].value && hand[1].value ==hand[2].value){

if(hand[3].value==hand[4].value && hand[3].value!=hand[2].value)
    return 1;
}
 return 0;   
}

int is_flush (hand_t hand) {
int i;
int suit=hand[0].suit;
if( hand[0].suit == hand[1].suit && hand[1].suit == hand[2].suit && hand[2].suit == hand[3].suit && hand[3].suit == hand[4].suit ) 
    return 1;

    return 0;
}


int is_straightflush (hand_t hand) {
 int suit = hand[0].suit;
    int i;

    for (i=1;i<5;i++)
        if (hand[i].suit!=suit)
            return 0;
return 1;
}

int is_fourofakind (hand_t hand) {
int i,fkind;
if(hand[0].value==hand[1].value && hand[1].value==hand[2].value && hand[2].value==hand[3].value && hand[3].value==hand[4].value){
fkind=1;
return 1;
}
else if(hand[0].value==hand[1].value && hand[1].value==hand[2].value && hand[2].value==hand[4].value){fkind++;
}
else if(hand[0].value==hand[1].value && hand[1].value==hand[2].value && hand[2].value==hand[3].value){fkind++;
}
else if(hand[0].value==hand[1].value && hand[1].value==hand[3].value && hand[3].value==hand[4].value){
fkind++;
}
else if(hand[1].value==hand[2].value && hand[2].value==hand[3].value && hand[3].value==hand[4].value){
fkind++;
}
else if(hand[0].value==hand[2].value && hand[2].value==hand[3].value && hand[3].value==hand[4].value){fkind++;
}

if(fkind>0) {
return 1;
}
return 0;
}
int is_royalflush (hand_t hand) {
if(hand[0].value=10 && hand[1].value==11 && hand[2].value==12 &&hand[3].value==13 && hand[4].value==14)
if( hand[0].suit == hand[1].suit && hand[1].suit == hand[2].suit && hand[2].suit == hand[3].suit && hand[3].suit == hand[4].suit )
return 1;  
  return 0;
}
int rank(hand_t h){
int rank = 0;
if(is_onepair(h)==1){
rank=1;
}
if(is_twopairs(h)==1){
rank=2;
}
if(is_threeofakind(h)==1){
rank=3;
}
if(is_fourofakind(h)==1){
rank=7;
}
if(is_straight(h)==1){
rank=4;
}
if(is_flush(h)==1){
rank=5;
}
if(is_fullhouse(h)==1){
rank=6;
}
if(is_straightflush(h)==1){
rank=8;
}
if(is_royalflush(h)==1){
rank=9;
}
return rank;
}
/* compares the hands based on rank -- if the ranks (and rank values) are
 * identical, compares the hands based on their highcards.
 * returns 0 if h1 > h2, 1 if h2 > h1.
 */

int compare_hands (hand_t h1, hand_t h2) {
sort_hand(h1);
sort_hand(h2);
if(rank(h2)>rank(h1)){
return 1;
}
if(rank(h2)<rank(h1)){
return 0;
}    
else {  

    return compare_highcards(h1, h2);
}
}
/* compares the hands based solely on their highcard values (ignoring rank). if
 * the highcards are a draw, compare the next set of highcards, and so forth.
 */

int compare_highcards (hand_t h1, hand_t h2) {
sort_hand(h1);
sort_hand(h2);
int i;
for(i=4;i>=0;i--){
if(h1[i].value<h2[i].value)
return 1;

else
return 0;
}
}
