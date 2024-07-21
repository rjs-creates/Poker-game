#pragma once
//Intializing an enum for the card value
typedef enum
{
	ace,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	queen,
	king,
}CardValue;

//enum for card suit
typedef enum
{
	diamond,
	club,
	heart,
	spade
}CardSuit;

//struct card containig its value and suit
typedef struct
{
	CardValue val;
	CardSuit suit;
}Cards;

typedef enum
{
	Pair,
	TwoPair,
	Three,
	Straight,
	Flush,
	FullHouse,
	Four,
	StraightFlush,
	RoyalFlush
}category;
