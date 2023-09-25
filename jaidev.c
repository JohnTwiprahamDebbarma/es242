#include "test.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
void generate_combinations(int a[], int n, int k, int b[], int start, int current, void *data, void (*process_combination)(int[], int, void *)) {
    if (current == k) {
        process_combination(b, k, data);
        return;
    }

    for (int i = start; i < n; i++) {
        b[current] = a[i];
        generate_combinations(a, n, k, b, i + 1, current + 1, data, process_combination);
    }
}



void process_selection(int combination[], int k, void *data) {
    for (int i = 0; i < k; i++) {
        printf("%d ", combination[i]);
    }
    printf("\n");
}

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int[], int, void *)) {
    generate_combinations(a, n, k, b, 0, 0, data, process_selection);
}


typedef struct {
    int index;
    int err;
    int first;
} state_t1;


static void test_selections_2165(int b[], int k, void *data)
{
    state_t1 *s = (state_t1 *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}


static void test_selections_123(int b[], int k, void *data)
{
    state_t1 *s = (state_t1 *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 3)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}


void count_selections(int b[], int k, void *data)
{
    int *d = (int*)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data)
{
    selection_t *s = (selection_t*)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}










/********************************************************************************************************/
/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
// Function to return bool value if all the strings in the input array of strings are present in the Dictionary array
bool findIfStringinDict(char smallerArray[100][100], int smallerSize, const char* DICTarr[], int DICTsize) {
    for (int i = 0; i < smallerSize; i++) {//Traversing all the elements in the dictionary
        bool found = false;//Init a flag variable that is a bool, initially false, that is the string found is false
        for (int j = 0; j < DICTsize; j++) {// Traversing all the elements of the dict to find the similarity
            if (strcmp(smallerArray[i], DICTarr[j]) == 0)
            {
                found = true;
                break;//Turning the found bool to true as soon as the string is found in the dict
            }
        }//If the particular string is not found after traversing the whole of the dict using the for loop, we will return a Fasle and the function is returnd with a false
        if (!found) {
            return false;
        }
    }
    return true;
}
// Remove the // and run that for checking
// int main() {
//     char* smallerArray[] = {"ART", "IS", "TOIL"};
//     int smallerSize = sizeof(smallerArray) / sizeof(smallerArray[0]);
//     char* DICTarr[] = {"ART", "IS", "OIL", "ARTIST", "TOIL"};
//     int DICTsize = sizeof(DICTarr) / sizeof(DICTarr[0]);
//     bool result = findIfStringinDict(smallerArray, smallerSize, DICTarr, DICTsize);
//     if (result) {
//         printf("All Present.\n");
//     } else {
//         printf("Some Absent\n");
//     }
//     return 0;
// }

typedef struct {
    char *correct[256];
    int ncorrect;
    int err;
} state_t;

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    if (s->ncorrect==0){
        s->err=0;
        
    }else{
    for (int i=0;i<s->ncorrect;i++){
        if (strcmp(buf,s->correct[i])==0){
            s->err=0;
        }
    }
    
    }
}
void printdict(char *result,const char *dictionary[],int nwords,char buf[],void *data,void (*process_split(char buf[], void *data))){
    int l = strlen(result);
    int si;
    int ei = 0;
    char tempArray[100][100]; 
    int tempCount = 0;
    for (int j = 0; j < l; j++) {
        if (result[j] == '{') {
            si = j;
        }
        if (result[j] == '}') {
            ei = j;
            char temp[100] = {""};
            strncpy(temp, result + si + 1, ei - si - 1);
            strcpy(tempArray[tempCount], temp); 
            tempCount++;
    
        }
    }
    bool ans = findIfStringinDict(tempArray,tempCount,dictionary,nwords);
    if (ans==true){
        strcpy(buf,"");
        for (int i=0;i<tempCount;i++){
            if (i==tempCount-1){
                strcat(buf,tempArray[i]);
            }else{
                strcat(buf,tempArray[i]);
                strcat(buf," ");
            }
        }
        process_split(buf,data);

    }
    
    
}
void subword(const char *s, int i, char *result,const char *dictionary[],int nwords,char buf[],void* data,void (*process_split(char buf[], void *data)))
{
    int n = strlen(s);
    if (i == n) {
        printdict(result,dictionary,nwords,buf,data,process_split);
        return;
    }

    for (int j = n - 1; j >= i; j--)
    {
        char substr[100];
        strncpy(substr, s + i, j - i + 1);
        substr[j - i + 1] = '\0';
        char new_result[100];
        strcpy(new_result, result);
        strcat(new_result, "{");
        strcat(new_result, substr);
        strcat(new_result, "}");

        subword(s, j + 1, new_result,dictionary,nwords,buf,data,process_split);
    }
}


void generate_splits(const char *source, const char *dictionary[], int nwords,char buf[],void *data,void (*process_split(char buf[], void *data))) {
    
    subword(source,0,"",dictionary,nwords,buf,data,process_split);

}





/********************************************************************************************************/
/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */
/* void previous_permutation(int a[], int n) {} */


// Provide the input as an Integer. The output will also be the integer. The input parameter is just the integer whose previous permutation needs to be calculated

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    int temp;

    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int convertDigitsToNumber(int arr[], int size) {
    int result = 0;
    int power = 1;
    for (int i = size - 1; i >= 0; i--) {
        result += arr[i] * power;
        power *= 10;
    }
    return result;
}

void selectionDescendSort(int arr[], int start, int end) {
    int i, j, maxIndex;

    for (i = start; i <= end; i++) {
        maxIndex = i;

        for (j = i + 1; j <= end; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }

        if (maxIndex != i) {
            swap(&arr[i], &arr[maxIndex]);
        }
    }
}

int findMaxIndexInRangeSmallerThanLimit(int array[], int start, int end, int limit) {
    int maxIndex = -1;
    int maxElement = -1;
    for (int i = start; i <= end; i++) {
        if (array[i] < limit && array[i] > maxElement) {
            maxElement = array[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

int generatePreviousPermutation(int num) {
// Convert the number into an array of digits
    int digits[100];
    int length = 0;// Length of the array
    int temp = num;
    bool asc = false;// Bool to check for the ascending order of the numbers
    while (temp > 0) {  // Convert the number into an array of digits
        digits[length++] = temp % 10;
        temp /= 10;
    }
    reverseArray(digits, length);
//    printArray(digits, length);
// Traverse the array to find the first pair of adjacent digits in descending order
    int i = length - 2;
    while (i >= 0 && digits[i] <= digits[i + 1]) {
        i--;
    }

// If no such pair is found, then the array is in the ascending order and hence return the original number and the message
// Here asc serves as the Flag for the next process
    if (i < 0) {
        printf("No previous permutation exists.\n");
        asc = true;
    }
if (asc == false){
    // Find the largest digit in the right side that is non decreasing
    int j = length - 1;
    while (digits[j] >= digits[j-1]) {
        j--;
    }
//    printf("%d\n", j);
// Now, find the next digit that is on the right side of the j such that it is the largest number just smaller than digits[j-1]
    int a;
    a = findMaxIndexInRangeSmallerThanLimit(digits, j, length-1, digits[j-1]);
//    printf("%d\n", a);
// Swap theses 2 numbers and sort the remaing right side part of the array in decreasing order
    swap(&digits[j-1], &digits[a]);
//    printArray(digits, length);
    selectionDescendSort(digits, j, length-1);
//    printArray(digits, length);
}
// Convert the array of digits back into a number
    int result = convertDigitsToNumber(digits, length);
    return result;
}


void previous_permutation(int a[], int n)
{
// Convert the number into an array of digits
//    int digits[100];
//    int length = 0;// Length of the array
//    int temp = num;
    bool asc = false;// Bool to check for the ascending order of the numbers
//    while (temp > 0) {  // Convert the number into an array of digits
//        digits[length++] = temp % 10;
//        temp /= 10;
//    }
//    reverseArray(digits, length);
//    printArray(digits, length);
// Traverse the array to find the first pair of adjacent digits in descending order
    int i = n - 2;
    while (i >= 0 && a[i] <= a[i + 1]) {
        i--;
    }

// If no such pair is found, then the array is in the ascending order and hence return the original number and the message
// Here asc serves as the Flag for the next process
    if (i < 0) {
 //       printf("No previous permutation exists.\n");
        asc = true;
    }
if (asc == false){
    // Find the largest digit in the right side that is non decreasing
    int j = n - 1;
    while (a[j] >= a[j-1]) {
        j--;
    }
//    printf("%d\n", j);
// Now, find the next digit that is on the right side of the j such that it is the largest number just smaller than digits[j-1]
    int anIndex;
    anIndex = findMaxIndexInRangeSmallerThanLimit(a, j, n-1, a[j-1]);
//    printf("%d\n", a);
// Swap theses 2 numbers and sort the remaing right side part of the array in decreasing order
    swap(&a[j-1], &a[anIndex]);
//    printArray(digits, length);
    selectionDescendSort(a, j, n-1);
//    printArray(digits, length);
}
//printArray(a, n);
    // return a;
}






///************************************************************************************************************************************************///

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[10];
    state_t1 s2165 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");

    int a1[] = { 1, 2, 3 };
    state_t1 s123 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a1, 3, 1, b, &s123, test_selections_123);
    ASSERT(!s123.err, "Failed on 1 2 3.");

    int c = 0;
    int aa[] = { 1, 5, 3, 0, 1, 12, 4, 3, 6, 6 };
    generate_selections(aa, 10, 5, b, &c, count_selections);
    ASSERT_EQ(c, 252, "Failed on 10C5.");

    selection_t s;
    generate_selections(aa, 10, 5, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 5, "Failed on last of 10C5.", 12, 4, 3, 6, 6);

    int c1 = 0;
    int aa1[] = { 7, 2, 8, 4, 9, 6 };
    generate_selections(aa1, 6, 4, b, &c1, count_selections);
    ASSERT_EQ(c1, 15, "Failed on 6C4.");

    int c2 = 0;
    int aa2[] = { 3, 1, 3 };
    generate_selections(aa2, 3, 3, b, &c2, count_selections);
    ASSERT_EQ(c2, 1, "Failed on 3C3.");

    int c3 = 0;
    int aa3[] = { 1, 2, 3 };
    generate_selections(aa3, 3, 1, b, &c3, count_selections);
    ASSERT_EQ(c3, 3, "Failed on 3C1.");

    int c4 = 0;
    int aa4[] = { 3 };
    generate_selections(aa4, 1, 1, b, &c4, count_selections);
    ASSERT_EQ(c4, 1, "Failed on 1C1.");

    selection_t s1;
    generate_selections(aa1, 6, 4, b, &s1, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s1.b, 4, "Failed on last of 6C4.", 8, 4, 9, 6);

    selection_t s2;
    generate_selections(aa2, 3, 3, b, &s2, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s2.b, 3, "Failed on last of 3C3.", 3, 1, 3);

    selection_t s3;
    generate_selections(aa3, 3, 1, b, &s3, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s3.b, 1, "Failed on last of 3C1.", 3);

    selection_t s4;
    generate_selections(aa4, 1, 1, b, &s4, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s4.b, 1, "Failed on last of 1C1.", 3);

} END_TEST




BEGIN_TEST(generate_splits) {
    const char a[] = "artistoil";
    const char* dict[] = {"art", "artist", "is", "oil", "toil"};
    char *correct_splits[256] = {"artist oil","art is oil"};
    int nwords = 5;
    int number_correct =2;
    state_t s = {.err = 1, .ncorrect = number_correct};
    for (int i = 0; i < number_correct; i++) {
    s.correct[i] = correct_splits[i];
    }
    char buf[256];
    void*func = test_splits_art;
    generate_splits(a, dict, nwords, buf, &s, func);
    ASSERT(!s.err, "Failed on 'artistoil' 1.");

    const char a2[] = "BOTHEARTHANDSATURNSPIN";
    const char* dict2[] = {"BOT","HEART","HAND","SAT","URNS","PIN"};
    char *correct_splits2[256] = {"BOT HEART HAND SAT URNS PIN"};
    int nwords2 = 6;
    int number_correct2 =1;
    state_t s2 = {.err = 1, .ncorrect = number_correct2};
    for (int i = 0; i < number_correct2; i++) {
    s2.correct[i] = correct_splits2[i];
    }
    char buf2[256];
    generate_splits(a2, dict2, nwords2, buf2, &s2, func);
    ASSERT(!s2.err, "Failed on 'BOTHEARTHANDSATURNSPIN'.");

    const char a3[] = "BOTHEARTHANDSATURNSPIN";
    const char* dict3[] = {"AND","BOT","BOTH","EARTH","HEART","HAND","SAT","SATURN","SPIN","URNS","PIN"};
    char *correct_splits3[256] = {"BOT HEART HAND SAT URNS PIN","BOTH EARTH AND SATURN SPIN","BOT HEART HAND SATURN SPIN","BOTH EARTH AND SAT URNS PIN"};
    int nwords3 = 11;
    int number_correct3 =4;
    state_t s3 = {.err = 1, .ncorrect = number_correct3};
    for (int i = 0; i < number_correct3; i++) {
    s3.correct[i] = correct_splits3[i];
    }
    char buf3[256];
    generate_splits(a3, dict3, nwords3, buf3, &s3, func);
    ASSERT(!s3.err, "Failed on 'BOTHEARTHANDSATURNSPIN' 2.");

    const char a4[] = "artistoil";
    const char* dict4[] = { "artist", "is", "oil"};
    int nwords4 = 3;
    int number_correct4 =0;
    state_t s4 = {.err = 1, .ncorrect = number_correct4};
    s4.correct[0] = "empty";
    char buf4[256];
    generate_splits(a4, dict4, nwords4, buf4, &s4, func);
    ASSERT(!s4.err, "Failed on 'artistoil' 2.");

    const char a5[] = "ABCDEF";
    const char* dict5[] = {"AB", "CD", "EF", "A", "B","C","D","E","F"};
    char *correct_splits5[256] = {"AB CD EF","A B C D E F"};
    int nwords5 = 9;
    int number_correct5 =2;
    state_t s5 = {.err = 1, .ncorrect = number_correct5};
    for (int i = 0; i < number_correct5; i++) {
    s5.correct[i] = correct_splits5[i];
    }
    char buf5[256];
    generate_splits(a5, dict5, nwords5, buf5, &s5, func);
    ASSERT(!s5.err, "Failed on 'ABCDEF'.");

    const char a6[] = "PINSTARTRAPSANDRAGSLAP";
    const char* dict6[] = {"PINS", "TART", "RAP", "SAND", "RAG","SLAP","PIN","STAR","TRAP","SAN","DRAG","START","RAPS","RAPS","AND","RAGS","LAP","TRAPS","AN","DRAGS"};
    char *correct_splits6[256] = {"PINS TART RAP SAND RAG SLAP","PIN STAR TRAP SAN DRAG SLAP","PIN START RAPS AND RAGS LAP","PIN STAR TRAPS AN DRAGS LAP"};
    int nwords6 = 20;
    int number_correct6 =4;
    state_t s6 = {.err = 1, .ncorrect = number_correct6};
    for (int i = 0; i < number_correct6; i++) {
    s6.correct[i] = correct_splits6[i];
    }
    char buf6[256];
    generate_splits(a6, dict6, nwords6, buf6, &s6, func);
    ASSERT(!s6.err, "Failed on 'PINSTARTRAPSANDRAGSLAP'.");

    const char a7[] = "ABCDEFGH";
    const char* dict7[] = {"ABC", "A", "B","C","D","E","F","G","H","DEFGH","GH","ABCDEFG"};
    char *correct_splits7[256] = {"A B C D E F GH","ABC D E F G H","A B C D E F G H","ABCDEFG H","ABC DEFGH"};
    int nwords7 = 12;
    int number_correct7 =5;
    state_t s7 = {.err = 1, .ncorrect = number_correct7};
    for (int i = 0; i < number_correct7; i++) {
    s7.correct[i] = correct_splits7[i];
    }
    char buf7[256];
    generate_splits(a7, dict7, nwords7, buf7, &s7, func);
    ASSERT(!s7.err, "Failed on 'ABCDEFGH'.");



} END_TEST






BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);

    int a1[] = { 1, 2, 3, 4, 5, 6 };
    previous_permutation(a1, 6);
    ASSERT_ARRAY_VALUES_EQ(a1, 6, "Failed on 1 2 3 4 5 6.", 1, 2, 3, 4, 5, 6);

    int a2[] = { 6, 5, 4, 3, 2, 1 };
    previous_permutation(a2, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a2, 6, "Failed on 6 5 4 3 2 1.", 6, 5, 4, 3, 1, 2);

    int a3[] = { 1, 1, 1, 1, 1, 1 };
    previous_permutation(a3, 6);
    ASSERT_ARRAY_VALUES_EQ(a3, 6, "Failed on 1 1 1 1 1 1.", 1, 1, 1, 1, 1, 1);

    int a4[] = { 9, 9, 9, 9, 9, 9 };
    previous_permutation(a4, 6);
    ASSERT_ARRAY_VALUES_EQ(a4, 6, "Failed on 9 9 9 9 9 9.", 9, 9, 9, 9, 9, 9);

    int a5[] = { 6, 6, 6, 6, 6, 6 };
    previous_permutation(a5, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a5, 6, "Failed on 6 6 6 6 6 6.", 6, 6, 6, 6, 6, 6);

    int a6[] = { 4, 3, 5, 2, 6, 1 };
    previous_permutation(a6, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a6, 6, "Failed on 4 3 5 2 6 1.", 4, 3, 5, 2, 1, 6);

    int a7[] = { 7, 4, 6, 2, 7, 2 };
    previous_permutation(a7, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a7, 6, "Failed on 7 4 6 2 7 2.", 7, 4, 6, 2, 2, 7);

    int a8[] = { 9, 8, 3, 7, 6, 2 };
    previous_permutation(a8, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a8, 6, "Failed on 9 8 3 7 6 2.", 9, 8, 3, 7, 2, 6);

    int a9[] = { 7, 1, 2, 3, 4, 5 };
    previous_permutation(a9, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a9, 6, "Failed on 7 1 2 3 4 5.", 5, 7, 4, 3, 2, 1);

    int a10[] = { 7, 8, 1, 2, 3, 4 };
    previous_permutation(a10, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a10, 6, "Failed on 7, 8, 1, 2, 3, 4.", 7, 4, 8, 3, 2, 1);

    int a11[] = { 6, 7, 8, 1, 2, 3 };
    previous_permutation(a11, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a11, 6, "Failed on 6 7 8 1 2 3.", 6, 7, 3, 8, 2, 1);

    int a12[] = { 6, 7, 8, 9, 1, 2 };
    previous_permutation(a12, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a12, 6, "Failed on 6 7 8 9 1 2.", 6, 7, 8, 2, 9, 1);

    int a13[] = { 5, 6, 7, 8, 9, 1 };
    previous_permutation(a13, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a13, 6, "Failed on 5 6 7 8 9 1.", 5, 6, 7, 8, 1, 9);

    int a14[] = { 1, 0, 0, 0, 0, 0 };
    previous_permutation(a14, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a14, 6, "Failed on 1 0 0 0 0 0.", 0, 1, 0, 0, 0, 0);

    int a15[] = { 1, 1, 0, 0, 0, 0 };
    previous_permutation(a15, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a15, 6, "Failed on 1 1 0 0 0 0.", 1, 0, 1, 0, 0, 0);

    int a16[] = { 1, 0, 1, 0, 0, 0 };
    previous_permutation(a16, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a16, 6, "Failed on 1 0 1 0 0 0.", 1, 0, 0, 1, 0, 0);

    int a17[] = { 1, 1, 1, 0, 0, 0 };
    previous_permutation(a17, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a17, 6, "Failed on 1 1 1 0 0 0.", 1, 1, 0, 1, 0, 0);

    int a18[] = { 1, 1, 1, 0, 1, 1 };
    previous_permutation(a18, 6); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a18, 6, "Failed on 1 1 1 0 1 1", 1, 1, 0, 1, 1, 1);

    int a19[] = { 1, 2, 3};
    previous_permutation(a19, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a19, 3, "Failed on 1 2 3.", 1, 2, 3);

    int a20[] = { 2, 1, 3};
    previous_permutation(a20, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a20, 3, "Failed on 2 1 3.", 1, 3, 2);

    int a21[] = { 3, 1, 2};
    previous_permutation(a21, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a21, 3, "Failed on 3 1 2.", 2, 3, 1);

    int a22[] = { 3, 2, 3};
    previous_permutation(a22, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a22, 3, "Failed on 3 2 3.", 2, 3, 3);

    int a23[] = { 2, 1};
    previous_permutation(a23, 2); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a23, 2, "Failed on 2 1", 1, 2);

    int a24[] = { 1, 2};
    previous_permutation(a24, 2); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a24, 2, "Failed on 1 2", 1, 2);

    int a25[] = { 2, 2};
    previous_permutation(a25, 2); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a25, 2, "Failed on 2 2", 2, 2);

    int a26[] = { 2};
    previous_permutation(a26, 1); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a26, 1,"Failed on 2", 2);

    int a27[] = {0, 2, 0, 1};
    previous_permutation(a27, 4); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(a27, 4,"Failed on 0201", 0, 1, 2, 0);
} END_TEST

/* Write your tests here. Use the previous assignment for reference. */
int main() {


    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(generate_splits),
            TEST(previous_permutation),
            0
        });
       

    return 0;

    
}