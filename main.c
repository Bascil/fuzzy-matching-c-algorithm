#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // Include math.h for fmin function

#define MAX_NAME_LENGTH 100
#define MAX_NAMES 1000

int levenshtein_distance(const char *s1, const char *s2);
double min(double a, double b, double c);

int levenshtein_distance(const char *s1, const char *s2) {
    // Calculate the lengths of strings s1 and s2
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // Initialize a matrix to store results of distance calculation
    int matrix[MAX_NAME_LENGTH][MAX_NAME_LENGTH];

    // Initialize the matrix
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 && j == 0)
                matrix[i][j] = 0;
            else if (i == 0)
                matrix[i][j] = matrix[i][j-1] + 1;
            else {
                if(tolower(s1[i-1]) == tolower(s2[j-1]))
                    matrix[i][j] = matrix[i-1][j-1];
                else
                    matrix[i][j] = 1 + min(matrix[i][j-1], matrix[i-1][j], matrix[i-1][j-1]);
            }
        }
    }

    // Return the Levenshtein distance between s1 and s2
    return matrix[len1][len2];
}

double min(double a, double b, double c) {
    if (a <= b && a <= c) {
        return a;
    } else if (b <= a && b <= c) {
        return b;
    } else {
        return c;
    }
}

int main() {
    char keyword[MAX_NAME_LENGTH];
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int num_names = 0;

    printf("Enter a keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    // Open the file for reading
    FILE *file = fopen("names.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_NAME_LENGTH];
    // Read each line from the file using fgets.
    while (fgets(line, sizeof(line), file)) {
        // Trim the newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';
        // If number of names read exceeds maximum allowed, print error
        if (num_names >= MAX_NAMES) {
            fprintf(stderr, "Maximum number of names exceeded\n");
            break;
        }
        strcpy(names[num_names], line);
        num_names++;
    }

    fclose(file);

    int num_results = 0;

    printf("\nFuzzy Matches for \"%s\":\n", keyword);
    for (int i = 0; i < num_names; i++) {
        int distance = levenshtein_distance(keyword, names[i]);
        if (distance <= 4) {  // You can adjust the threshold as needed
            printf("%s (Distance: %d)\n", names[i], distance);
            num_results++;
        }
    }

    printf("\nNumber of results: %d\n", num_results);

    return 0;
}