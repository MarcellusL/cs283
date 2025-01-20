#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SZ 50

// prototypes
void usage(char *);
void print_buff(char *, int);
int setup_buff(char *, char *, int);

// prototypes for functions to handle required functionality
int count_words(char *, int, int);
// add additional prototypes here

int setup_buff(char *buff, char *user_str, int len)
{
    // TODO: #4:  Implement the setup buff as per the directions

    int processed_str = 0;
    int prev_was_whitespace = 1;
    const char *read_ptr = user_str;
    char *write_ptr = buff;

    while (*read_ptr != '\0')
    {
        char current_str = *read_ptr;

        if (current_str == ' ' || current_str == '\t')
        {
            if (!prev_was_whitespace)
            {
                if (processed_str >= len)
                {
                    return -1;
                }
                *write_ptr = ' ';
                write_ptr++;
                processed_str++;
                prev_was_whitespace = 1;
            }
        }
        else
        {
            if (processed_str >= len)
            {
                return -1;
            }
            *write_ptr = current_str;
            write_ptr++;
            processed_str++;
            prev_was_whitespace = 0;
        }
        read_ptr++;
    }

    if (processed_str > 0 && *(write_ptr - 1) == ' ')
    {
        write_ptr--;
        processed_str--;
    }

    int user_str_len = processed_str;

    // Any space left is filled with dots
    for (int i = processed_str; i < len; i++)
    {
        buff[i] = '.';
    }

    return user_str_len; // for now just so the code compiles.
}

void print_buff(char *buff, int len)
{
    printf("Buffer:  ");
    for (int i = 0; i < len; i++)
    {
        putchar(*(buff + i));
    }
    putchar('\n');
}

void usage(char *exename)
{
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);
}

int count_words(char *buff, int len, int str_len)
{
    // YOU MUST IMPLEMENT

    int word_count = 0;
    int in_word = 0;

    for (int i = 0; i < str_len; i++)
    {
        if (buff[i] != ' ' && !in_word)
        {
            word_count++;
            in_word = 1;
        }
        else if (buff[i] == ' ')
        {
            in_word = 0;
        }
    }
    return word_count;
}

// ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS
int reverse_string(char *buff, int len, int str_len)
{
    for (int i = str_len - 1; i >= 0; i--)
    {
        printf("%c", buff[i]);
    }
    printf("\n");
    return 0;
}

int word_print(char *buff, int len, int str_len)
{
    if (buff == NULL || str_len > len || str_len <= 0)
    {
        return -1;
    }

    int word_start = 0;
    int word_num = 1;
    int i = 0;

    printf("Word Print\n");
    printf("----------\n");

    while (i < str_len)
    {
        while (i < str_len && buff[i] != ' ')
        {
            i++;
        }

        int word_len = i - word_start;

        printf("%d. ", word_num);
        for (int j = word_start; j < i; j++)
        {
            printf("%c", buff[j]);
        }
        printf(" (%d)\n", word_len);

        while (i < str_len && buff[i] == ' ')
        {
            i++;
        }

        word_start = i;
        word_num++;
    }
    return 0;
}

int search_and_replace(char *buff, int len, int str_len, const char *search, const char *replace)
{

    int search_len = 0;
    int replace_len = 0;
    int i;
    int string_index = -1;

    while (search[search_len] != '\0')
        search_len++;
    while (replace[replace_len] != '\0')
        replace_len++;

    for (i = 0; i <= str_len - search_len; i++)
    {
        int match = 1;
        for (int j = 0; j < search_len; j++)
        {
            if (buff[i + j] != search[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
        {
            string_index = i;
            break;
        }
    }

    if (string_index == -1)
    {
        printf("Search string not found\n");
        return -1;
    }

    // Check for if replacement would go beyond the length of the buffer
    int new_length = str_len - search_len + replace_len;
    if (new_length > len)
    {
        printf("Error: String replacement would exceed buffer size\n");
        return -1;
    }

    if (replace_len != search_len)
    {
        for (i = str_len - 1; i >= string_index + search_len; i--)
        {
            buff[i + (replace_len - search_len)] = buff[i];
        }
    }

    // Inserts replacement string
    for (i = 0; i < replace_len; i++)
    {
        buff[string_index + i] = replace[i];
    }

    // Any space left is filled with dots
    for (i = new_length; i < len; i++)
    {
        buff[i] = '.';
    }

    // Prints the updated string
    printf("Modified String: ");
    for (i = 0; i < new_length; i++)
    {
        printf("%c", buff[i]);
    }
    printf("\n");

    return new_length;
}

int main(int argc, char *argv[])
{

    char *buff;         // placehoder for the internal buffer
    char *input_string; // holds the string provided by the user on cmd line
    char opt;           // used to capture user option from cmd line
    int rc;             // used for return codes
    int user_str_len;   // length of user supplied string

    // TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //       PLACE A COMMENT BLOCK HERE EXPLAINING
    /*
        This is safe because its a check on if enough arguments
        were given in the input to access argv[1]. If argv[1] doesn't
        exist, the program will detect the dash, call usage to output
        correct format, and exit.
    */
    if ((argc < 2) || (*argv[1] != '-'))
    {
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1] + 1); // get the option flag

    // handle the help flag and then exit normally
    if (opt == 'h')
    {
        usage(argv[0]);
        exit(0);
    }

    // WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    // TODO:  #2 Document the purpose of the if statement below
    //       PLACE A COMMENT BLOCK HERE EXPLAINING
    /*
        This is a check for if the command line has less than 3 arguments
        on the command line. If true for less than 3 arguments, it will call
        usage, print to output, and return 1.
    */
    if (argc < 3)
    {
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; // capture the user input string

    // TODO:  #3 Allocate space for the buffer using malloc and
    //           handle error if malloc fails by exiting with a
    //           return code of 99
    //  CODE GOES HERE FOR #3
    buff = (char *)malloc(BUFFER_SZ);
    if (buff == NULL)
    {
        fprintf(stderr, "Malloc failed");
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ); // see todos
    if (user_str_len < 0)
    {
        printf("Error setting up buffer, error = %d\n", user_str_len);
        exit(3);
    }

    switch (opt)
    {
    case 'c':
        rc = count_words(buff, BUFFER_SZ, user_str_len); // you need to implement
        if (rc < 0)
        {
            printf("Error counting words, rc = %d\n", rc);
            free(buff);
            exit(3);
        }
        printf("Word Count: %d\n", rc);
        print_buff(buff, BUFFER_SZ);
        break;

        // TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //        the case statement options

    case 'r':
        rc = reverse_string(buff, BUFFER_SZ, user_str_len);
        if (rc < 0)
        {
            printf("Error reversing string, rc = %d\n", rc);
            free(buff);
            exit(3);
        }
        break;

    case 'w':
        rc = word_print(buff, BUFFER_SZ, user_str_len);
        if (rc < 0)
        {
            printf("Error word printing, rc = %d\n", rc);
            free(buff);
            exit(3);
        }
        print_buff(buff, BUFFER_SZ);
        break;

    case 'x':
        if (argc != 5)
        {
            printf("Error Command needs 5 arguments\n");
            free(buff);
            exit(1);
        }
        rc = search_and_replace(buff, BUFFER_SZ, user_str_len, argv[3], argv[4]);
        if (rc < 0)
        {
            free(buff);
            exit(3);
        }
        print_buff(buff, BUFFER_SZ);
        break;

    default:
        usage(argv[0]);
        exit(1);
    }

    // TODO:  #6 Dont forget to free your buffer before exiting
    free(buff);
    exit(0);
}

// TODO:  #7  Notice all of the helper functions provided in the
//           starter take both the buffer as well as the length.  Why
//           do you think providing both the pointer and the length
//           is a good practice, after all we know from main() that
//           the buff variable will have exactly 50 bytes?
//
/*
            Why I think providing both the pointer and the length is a good
            practice since the buffer size can be provided to each individual
            function, along with providing the length. It helps avoid in having
            a hardcoded buffer size, which could cause issue if the buffer size
            was to change dynamically.
*/