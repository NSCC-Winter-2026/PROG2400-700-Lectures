#include <iostream>
using namespace std;

// Recursive function
bool checkPalindrome(string& word, int left, int right) {
    // Base case, if pointers cross it's a palindrome
    if (left >= right)
        return true;

    // If characters at current positions don't match, then it's not a palindrome
    if (word[left] != word[right])
        return false;

    // Moves inward and checks the remaining substring
    return checkPalindrome(word, left + 1, right - 1);
}

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    // Calls the function starting from the first and last index
    if (checkPalindrome(word, 0, word.length() - 1))
        cout << word << " is a palindrome." << endl;
    else
        cout << word << " is NOT a palindrome." << endl;

    return 0;
}
