/*
Name: Jeffery Knudson
Program: Assignment 5 - DoublyLinkedList
Part: Driver
Date: 11/8/19
*/
#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;

void check(int expectedVal, int actualVal)
{
	cout << "Expected: " << expectedVal << endl << "Actual: " << actualVal << endl;
	cout << (actualVal == expectedVal ? "Passed" : "Failed") << endl << endl;
}

int main()
{
	DoublyLinkedList<int> *myList = new DoublyLinkedList<int>();
	int expected;
	int actual;
	myList->addFirst(5);
	myList->addFirst(7);
	myList->addLast(3);

	cout << "Get Size Test:" << endl;
	{
		expected = 3;
		actual = myList->getSize();
		check(expected, actual);
	}

	cout << "Get First Test:" << endl;
	{
		expected = 7;
		actual = myList->getFirst();
		check(expected, actual);
	}

	cout << "Get Last Test:" << endl;
	{
		expected = 3;
		actual = myList->getLast();
		check(expected, actual);
	}

	cout << "Remove First Test:" << endl;
	{
		myList->removeFirst();
		expected = 5;
		actual = myList->getFirst();
		check(expected, actual);
	}

	cout << "Remove Last Test:" << endl;
	{
		myList->removeLast();
		expected = 5;
		actual = myList->getLast();
		check(expected, actual);
	}

	cout << "Remove All Test:" << endl;
	{
		myList->removeFirst();
		cout << "Expected: Exception" << endl;
		try
		{
			myList->removeFirst();
			cout << "Actual: Runs Through" << endl;
			cout << "Failed" << endl;
		}
		catch (exception a)
		{
			cout << "Actual: Exception" << endl;
			cout << "Passed" << endl;
		}
	}

	myList->addFirst(6);
	myList->addFirst(4);
	myList->addLast(3);

	cout << endl;
	cout << "Clear Test: (1 being true, 0 being false for isEmpty)" << endl;
	{
		expected = 1;
		myList->clear();
		actual = (myList->isEmpty() ? 1 : 0);
		check(expected, actual);
	}

	cout << "Removal When List is Empty Test:" << endl;
	{
		int exceptionCount = 0;
		expected = 2;
		try
		{
			myList->removeFirst();
		}
		catch (exception)
		{
			exceptionCount++;
		}

		try
		{
			myList->removeLast();
		}
		catch (exception)
		{
			exceptionCount++;
		}

		check(expected, exceptionCount);
	}

	myList->addFirst(5);
	myList->addLast(6);
	myList->addLast(4);
	myList->addFirst(2);
	cout << "Print Output Test" << endl;
	{
		cout << "This one passes or fails based on output." << endl;
		cout << "Expected: [2, 5, 6, 4]" << endl;
		cout << "Actual: " << *myList << endl;
	}
	cout << endl;
	myList->clear();
	cout << "Print Empty Test" << endl;
	{
		cout << "This test passes or fails based on output" << endl;
		cout << "Expected: []" << endl;
		cout << "Actual: " << *myList << endl;
	}
	return 0;
}
