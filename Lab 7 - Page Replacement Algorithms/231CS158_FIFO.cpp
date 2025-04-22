// C++ program to simulate FIFO Paging
#include <iostream>
#include <unordered_map>

#define MAX_SIZE 50

using namespace std;

// Initialize a global array of frames, along with some necessary global variables
int frames[MAX_SIZE];
int size = 0, t = 0, capacity, page_fault = 0;

// Initialize a global hash map to store the time of entry of each page
unordered_map<int, int> pages;

// Function to simulate FIFO paging
void FIFOPaging(int page)
{
    // If all the frames are not filled yet
    if (size < capacity) {
        for (int i=0; i < capacity; i++) {
            // If the page already exists in a frame, print appropriate message and return
            if (frames[i] == page) {
                t++;
                cout << "Page " << page << " is already present at Frame " << i << endl;
                return;
            }
        }
        // If the page does not exist in a frame, increase page fault and add the page to a frame
        cout << "Page " << page << " accomodated at Frame " << size << endl;

        frames[size++] = page;
        page_fault++;
        pages[page] = t++;
        return;
    }

    // If all the frames are filled
    int fifo_t = INT_MAX, val;
    for (int i=0; i < capacity; i++) {
        // If the page already exists in a frame, print appropriate message and return 
        if (frames[i] == page) {
            t++;
            cout << "Page " << page << " is already present at Frame " << i << endl;
            return;
        }
    }
    // If the page does not exist in a frame, find the First In page to remove
    for (int j=0; j < capacity; j++) {
        if (pages[frames[j]] < fifo_t) {
            fifo_t = pages[frames[j]];
            val = j;
        }
    }
    // Print the appropriate message, increase page fault and add the page to a frame
    cout << "Page " << page << " accomodated at Frame " << val << " after removing Page " << frames[val] <<  endl;

    frames[val] = page;
    page_fault++;
    pages[page] = t++;
}

// Driver Function
int main() {
    int choice, pno, res;
    float n_in = 0;

    // Check for positive integer input
    do {
        cout << "\nEnter the number of frames: ";
        cin >> capacity;
    } while (capacity <= 0);

    // Program Menu will always show unless the user decides to quit
    while (true) {
        cout << "\n\n      PROGRAM MENU\n";
        cout << "-------------------------\n";
        cout << "1. Insert Page using FIFO\n";
        cout << "2. Quit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << "-------------------------\n";

        // Switch based on user inputted choice
        switch(choice) {
            // FIFO Paging case
            case 1: {
                cout << "\nEnter the page number: ";
                cin >> pno;
                FIFOPaging(pno);

                break;
            }
            // Quit case
            case 2: {
                cout << "\nTotal Page Faults: " << page_fault;
                cout << "\nPage Fault Ratio: " << page_fault / n_in;
                cout << "\n\nThanks for using my program!\n\n";
                exit(0);
            }
            // Default case for invalid input
            default: cout << "\nInvalid choice entered, try again...";
        }
        // Increment the value of n_in for number of inputs
        n_in++;
    }

    return 0;
}