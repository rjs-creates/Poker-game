#include <stdlib.h>
#include <stdio.h>
#include "card.h"

int main(int argc, char** argv)
{

	Cards deck[52];               //An array of 52 cards
	int counter = 0;              //Counter for the index of Array
	Cards Set[4][5];              //Two dimensional Array storing 4 players hands


	int Players[4] = { 1,-1,-1,-1 };   //Array storing int value of each player's highest Rank
	int counter2 = 0;                  //Counter to give away cards

	//Looping through all the suits
	for (int i = diamond; i <= spade; i++)
	{
		//Looping through all the values
		for (int j = ace; j <= king; j++)
		{
			//Assigning particular values to a card
			Cards card = { j,i };

			//Storing that card in the Array of cards
			deck[counter] = card;

			//Incrementing the index
			counter++;
		}
	}

	//Shuffling and printing the deck again
	shuffle(deck);

	//Giving each player there hand
	for (int incrementor = 0; incrementor < 4; incrementor++)
	{
		for (int j = 0; j < 5; j++)
		{
			//Storing the card Value in the array
			Set[incrementor][j] = deck[counter2];
			counter2++;
		}
	}

	//Showing each player's Hand
	for (int incrementor = 0; incrementor < 4; incrementor++)
	{
		printf("Player %d\n============\n", incrementor + 1);

		//Calling function Show hand
		ShowHand(Set[incrementor]);

		printf("\n");
	}

	printf("Winners\n==========\n");

	//Filling the array with the highest rank value of each player's hand
	for (int i = 0; i < 4; i++)
	{
		Players[i] = HighestRank(Set[i]);
	}

	//Finding the winner
	Winner(Players, deck);
}
