/************************************************************
 *  File:       Card.c
 *  Project:    Lab 2
 *  Author:     Rajeshwar Singh
 *  Version:    1.0
 *  Date:       16 March 2020
 *  Course:     CMPE1700
 *  Instructor: AJ Armstrong
 *  Description: Contains function to manipulate the deck of cards and hands
 * *********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "card.h"
#include <time.h>

 /*********************************************************************
  * Function:    ShowHand
  * Arguments:   Cards Deck[]
  * Returns:     void
  * Description: Prints the hand of all players
  * ******************************************************************/
  //Function to show the card
void ShowHand(Cards Deck[])
{
	//Looping between all the cards in the deck
	for (int i = 0; i < 5; i++)
	{
		//Checking the value of card and printing its respective value
		switch (Deck[i].val)
		{
		case 0: printf("Ace of ");
			break;
		case 1: printf("Two of");
			break;
		case 2: printf("Three of");
			break;
		case 3: printf("Four of");
			break;
		case 4: printf("Five of");
			break;
		case 5: printf("Six of");
			break;
		case 6: printf("Seven of");
			break;
		case 7: printf("Eight of ");
			break;
		case 8: printf("Nine of");
			break;
		case 9: printf("Ten of");
			break;
		case 10: printf("Jack of");
			break;
		case 11: printf("Queen of");
			break;
		case 12: printf("King of");
			break;
		}

		//Checking card suit and printing its suit
		switch (Deck[i].suit)
		{
		case 0: printf(" Diamond\n");
			break;
		case 1: printf(" Clubs\n");
			break;
		case 2: printf(" Hearts\n");
			break;
		case 3: printf(" Spades\n");
			break;
		}
	}

}

/*********************************************************************
 * Function:    shuffle
 * Arguments:   Cards Deck[]
 * Returns:     Card* - Card struct With shuffled values
 * Description: shuffle a deck of cards
 * ******************************************************************/
 //Function to shuffle cards
Cards* shuffle(Cards Deck[])
{
	srand(time(NULL));

	//Looping between all the cards
	for (int i = 0; i < 52; i++)
	{
		//Random value between 0 and i
		int j = rand() % (i + 1);

		//Picking a card with i index
		Cards PickedCard = Deck[i];

		//Inter Changing that card value of card with index i to a card with j index
		Deck[i] = Deck[j];
		Deck[j] = PickedCard;
	}
	//Returning the deck
	return Deck;
}

/*********************************************************************
 * Function:    Order
 * Arguments:   Cards* Set
 * Returns:     int - returns enum values of the ranks possible in a hand
 * Description: Check if the hand is Royal Flush,Straight flush,flush or straight
 * ******************************************************************/
int Order(Cards* Set)
{
	//Array of All the possible suits and Cards
	int PossibleCards[13] = { 0 };
	int PossibleSuit[4] = { 0 };

	int Val = 0;
	int Suit = 0;
	int StraightCheck = 0;
	int RoyalFlushCheck = 0;

	for (int i = 0; i < 5; i++)
	{
		//Value of card
		Val = Set[i].val;

		//Suit of the Card
		Suit = Set[i].suit;

		//Incrementing at the position where the Value of the card would be
		PossibleCards[Val] += 1;

		//Incrementing at the position where the Suit of the card would be
		PossibleSuit[Suit] += 1;
	}

	for (int i = 0; i < 13; i++)
	{
		//If the one card of 10,Jack,Queen,King,Ace
		if (PossibleCards[i + 9] == 1)
		{
			RoyalFlushCheck++;
		}
		//If the Cards are in Accending Sequence
		if (PossibleCards[i] == 1)
		{
			StraightCheck++;
		}
		else
		{
			StraightCheck = 0;
		}
		if (StraightCheck == 5)
			break;
	}
	for (int i = 0; i < 5; i++)
	{
		//If the suits of all the cards are same
		if (PossibleSuit[i] == 5)
		{
			//If all the cards are 10 or above
			if (RoyalFlushCheck == 5)
			{
				return RoyalFlush;
			}
			//If all the cards are in accending sequence
			if (StraightCheck == 5)
			{
				return StraightFlush;
			}
			//IF all the cards are just the same suit
			else
			{
				return Flush;
			}
		}
		else
		{
			//if cards of different suits are in acsending order
			if (StraightCheck == 5)
			{
				return Straight;
			}
		}
	}
	return -1;
}

/*********************************************************************
 * Function:    Rankings
 * Arguments:   Cards* Set
 * Returns:     int - returns enum values of the ranks possible in a hand
 * Description: Check if the hand is Full house, Four of a kind, Three of a kind, Two pairs or pair
 * ******************************************************************/
int Rankings(Cards* Set)
{
	//The Array storing the value that a hand has
	int PossibleCards[13] = { 0 };
	int Val;

	for (int i = 0; i < 4; i++)
	{
		//Value of card
		Val = Set[i].val;

		//Incrementing at the position where the Value of the card would be
		PossibleCards[Val] += 1;
	}

	//Looping through the Array with all the value of cards in a hand
	for (int i = 0; i < 13; i++)
	{
		//If 4 cards have the same value
		if (PossibleCards[i] == 4)
		{
			return Four;
		}

		//If 3 Cards have the same value
		if (PossibleCards[i] == 3)
		{
			for (int j = 0; j < 13; j++)
			{
				//Checking if the other two cards are the same value
				if (PossibleCards[j] == 2)
					return FullHouse;
			}
			return Three;
		}

		//If two cards with same value
		if (PossibleCards[i] == 2)
		{
			for (int j = 0; j < 13; j++)
			{
				//Checking if there's another pair in 3 left cards
				if (j != i && PossibleCards[j] == 2)
				{
					return TwoPair;
				}
			}
			return Pair;
		}
	}
	return -1;
}

/*********************************************************************
 * Function:    HighestRank
 * Arguments:   Cards* Set
 * Returns:     int - returns the highest rank in a hand
 * Description: Puts the Card pointer in the functions and get the highest
 * Rank in the hand
 * ******************************************************************/
int HighestRank(Cards* Set)
{
	int checkSuit;  //Int Value received from first order function
	int checkCard;  //Int value received from second Rankings function

	//Getting the int value for a hand
	checkSuit = Order(Set);
	checkCard = Rankings(Set);

	//if the value from Second function is greater
	if (checkCard > checkSuit)
	{
		return checkCard;
	}

	//If the value from first function is greater
	else if (checkCard < checkSuit)
	{
		return checkSuit;
	}

	//IF there was no rank in the hand
	else
	{
		return checkCard;
	}
}


/*********************************************************************
 * Function:    Winner
 * Arguments:   int* Players, Cards deck[]
 * Returns:     void- Prints the winner
 * Description: Gets the int value of highest rank of all players and find out the winner
 * ******************************************************************/
void Winner(int* Players, Cards deck[])
{
	int highCard = -1;          //Value of highCard
	int highCardPos = -1;       //Position of the highest Card
	int WinnerVal;              //Winning Value
	int WinnerPlayer;           //Winnning Player

	//Default Value of Winning
	WinnerVal = -1;

	//Default Winner
	WinnerPlayer = -1;

	//IF no one gets even a pair
	int noWin = 0;

	//Get the highest Rank from each players hand
	for (int i = 0; i < 4; i++)
	{
		//Greater than previous highes
		if (Players[i] > WinnerVal)
		{
			//New highest Values
			WinnerVal = Players[i];
			WinnerPlayer = i + 1;
		}
		//IF no rank
		if (Players[i] == -1)
		{
			//Player is not a winner yet
			noWin++;
		}
	}

	//IF no one got any rank
	if (noWin == 4)
	{
		//Check for the player with highest value card
		for (int i = 0; i < 20; i++)
		{
			//Checking for highest value
			if (deck[i].val > highCard)
			{
				highCard = deck[i].val;
				highCardPos = i;
			}
			//Checking for ace
			if (deck[i].val == 0)
			{
				highCard = deck[i].val;
				highCardPos = i;
				break;
			}
		}
		//Printing the result
		int Pos = (highCardPos + 1) / 5 + 1;
		printf("Player %d won with Ace as HighCard", Pos);
	}
	//If Players did get a rank in there hands
	else
	{
		//Giving the result based on players value
		if (WinnerVal == 8)
		{
			printf("Player %d won with Royal Flush", WinnerPlayer);
		}

		if (WinnerVal == 7)
		{
			printf("Player %d won with Straight Flush", WinnerPlayer);
		}

		if (WinnerVal == 6)
		{
			printf("Player %d won with four of a kind", WinnerPlayer);
		}

		if (WinnerVal == 5)
		{
			printf("Player %d won with full house", WinnerPlayer);
		}

		if (WinnerVal == 4)
		{
			printf("Player %d won with Flush", WinnerPlayer);
		}

		if (WinnerVal == 3)
		{
			printf("Player %d won with Straight", WinnerPlayer);
		}

		if (WinnerVal == 2)
		{
			printf("Player %d won with Three of a kind", WinnerPlayer);
		}

		if (WinnerVal == 1)
		{
			printf("Player %d won with Two Pair", WinnerPlayer);
		}

		if (WinnerVal == 0)
		{
			printf("Player %d won with Pair", WinnerPlayer);
		}
	}
}
