#include <stdio.h>
typedef struct state{
    int number;
    int count;
    int opCount;
    int currentSum;
    int nums[10];
    char operators[10];
}State;

void setNullState(State* aState){
    aState->count=0;
    aState->opCount=0;
    aState->currentSum=0;
    aState->number=0;

    for(int i=0 ; i <= 8 ; i++ ){
        aState->nums[i]=0;
        if ( i < 8 ){
            aState->operators[i]='*';
        }
    }
}

void printState(State* aState){
    for(int i=0 ; i < aState->count ; i++){
        if(i!=0)
            printf("%c ",aState->operators[i]);
        printf("%d ",aState->nums[i]);

    }
    printf("= %d\n",aState->currentSum);
}

void copyState(State* oldState ,State* newState){

    for(int i=0 ; i <= 8 ; i++ ){
        newState->nums[i]=oldState->nums[i];
        if ( i <= 8 ){
            newState->operators[i]=oldState->operators[i];
        }
    }
    newState->count=oldState->count;
    newState->opCount=oldState->opCount;
    newState->currentSum=oldState->currentSum;
    newState->number=oldState->number;
}

int nextStates(State* aState ){
    if(aState->number==-10000 ){
        if(aState->operators[0]!='-') {
            if (aState->currentSum == 100) {
                printState(aState);
            }
        }
        return 0;

    }

    State newState;
    copyState(aState,&newState);
    if(newState.number>=8){ ///here
        if(newState.number >=9){
            newState.number=-10000;
            nextStates(&newState);
        }else{
            int number=newState.number+1;
            newState.number=-10000;
            newState.nums[newState.count]=number;
            newState.operators[newState.opCount]='+';
            newState.count++;
            newState.opCount++;
            newState.currentSum+=number;
            nextStates(&newState);
            newState.operators[newState.opCount-1]='-';
            newState.currentSum-=number;
            newState.currentSum-=number;
            nextStates(&newState);
        }
        return 0;
    }

    //add , subtruct number
    newState.number+=1;
    newState.nums[newState.count]=newState.number;
    newState.operators[newState.opCount]='+';
    newState.count++;
    newState.opCount++;
    newState.currentSum+=newState.number;
    nextStates(&newState);
    newState.operators[newState.opCount-1]='-';
    newState.currentSum-=newState.number;
    newState.currentSum-=newState.number;
    nextStates(&newState);
    //make a set
    newState.currentSum+=newState.number;
    int set=newState.number * 10 + newState.number +1;
    newState.number++;
    newState.nums[newState.count-1]=set;
    newState.currentSum-=set;
    nextStates(&newState);
    newState.operators[newState.opCount-1]='+';
    newState.currentSum+=set;
    newState.currentSum+=set;
    nextStates(&newState);
    if(newState.number<8) {
        //make 3 digit set
        newState.currentSum -= set;
        set = (newState.number-1) * 100 + (newState.number) * 10 + newState.number + 1;
        newState.number++;
        newState.nums[newState.count - 1] = set;
        newState.currentSum -= set;
        nextStates(&newState);
        newState.operators[newState.opCount - 1] = '+';
        newState.currentSum += set;
        newState.currentSum += set;
        nextStates(&newState);
    }
    return 1 ;
}

int main() {
    State aState;
    setNullState(&aState);
    nextStates(&aState);
}