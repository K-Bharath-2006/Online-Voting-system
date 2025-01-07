#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATES 5
#define MAX_VOTERS 70

typedef struct {
    char name[50];
    int votes;
} Candidate;

typedef struct {
    int id;
    bool hasVoted;
} Voter;

Candidate candidates[MAX_CANDIDATES];
Voter voters[MAX_VOTERS];
int numCandidates = 0, numVoters = 0, totalVotes = 0;
int i; 
int j;

bool adminLogin() {
    char password[20];
    printf("\nEnter Admin Password: ");
    scanf("%s", password);
    if (strcmp(password, "admin@123") == 0) {
        printf("Admin Login Successful!\n");
        return true;
    } else {
        printf("Invalid Password! Access Denied.\n");
        return false;
    }
}

void addCandidates() {
    printf("Enter the number of candidates (max %d): ", MAX_CANDIDATES);
    scanf("%d", &numCandidates);

    if (numCandidates > MAX_CANDIDATES || numCandidates <= 0) {
        printf("Invalid number of candidates!\n");
        return;
    }

    for (i = 0; i < numCandidates; i++) {
        printf("Enter the name of candidate %d: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
    }
    printf("\nCandidates added successfully!\n");
}

void removeCandidate() {
    char candidateName[50];
    printf("\nEnter the name of the candidate to remove: ");
    scanf("%s", candidateName);

    for (i = 0; i < numCandidates; i++) {
        if (strcmp(candidates[i].name, candidateName) == 0) {
            for (j = i; j < numCandidates - 1; j++) {
                candidates[j] = candidates[j + 1];
            }
            numCandidates--;
            printf("Candidate %s removed successfully!\n", candidateName);
            return;
        }
    }
    printf("Candidate not found!\n");
}


void castVote() {
    int voterID;
    int choice;

    if (numCandidates == 0) {
        printf("\nNo candidates available to vote for! Contact Admin.\n");
        return;
    }

    printf("Enter your Voter ID to vote : ");
    scanf("%d", &voterID);

    bool found = false;
    for (i = 0; i < numVoters; i++) {
        if (voters[i].id == voterID) {
            found = true;
            if (voters[i].hasVoted) {
                printf("You have already voted! Duplicate votes are not allowed.\n");
                return;
            } else {
                voters[i].hasVoted = true; 
                break;
            }
        }
    }
    if (!found) {
        printf("Invalid Voter ID! Access denied.\n");
        return;
    }

  
    printf("\nVote for your candidate:\n");
    for (i = 0; i < numCandidates; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
    printf("Enter your choice (1-%d): ", numCandidates);
    scanf("%d", &choice);

    if (choice < 1 || choice > numCandidates) {
        printf("Invalid choice! Vote not counted.\n");
    } else {
        candidates[choice - 1].votes++;
        totalVotes++;
        printf("Vote cast successfully for %s!\n", candidates[choice - 1].name);
    }
}


void calculateResults() {
    if (numCandidates == 0) {
        printf("\nNo candidates available. Add candidates first.\n");
        return;
    }

    printf("\n--- Voting Results ---\n");
    for (i = 0; i < numCandidates; i++) {
        double percentage = (totalVotes > 0) ? ((double)candidates[i].votes / totalVotes) * 100 : 0;
        printf("%s: %d votes (%.2f%%)\n", candidates[i].name, candidates[i].votes, percentage);
    }
}


void declareWinner() {
    if (numCandidates == 0) {
        printf("\nNo candidates available. Add candidates first.\n");
        return;
    }

    int maxVotes = 0, winnerIndex = -1;
    bool tie = false;

    for (i = 0; i < numCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
            tie = false;
        } else if (candidates[i].votes == maxVotes) {
            tie = true;
        }
    }

    if (tie) {
        printf("\nIt's a tie! No clear winner.\n");
    } else {
    	 printf("\n------- Winner --------\n");
        printf("\nThe Winner is %s with %d votes!\n", candidates[winnerIndex].name, maxVotes);
    }
}

void resetSystem() {
    numCandidates = 0;
    numVoters = 0;
    totalVotes = 0;
    printf("\nSystem reset successfully! All data has been cleared.\n");
}

int main() {
    int role, adminChoice;

    printf("\t\t\t\t\t-------- Online Voting System --------\t\t\n");

    for (i = 0; i < MAX_VOTERS; i++) {
        voters[i].id = i + 1;
        voters[i].hasVoted = false;
    }
    numVoters = MAX_VOTERS;

    do {
        printf("\nChoose your role:\n");
        printf("1. Admin\n");
        printf("2. Voter\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &role);

        switch (role) {
            case 1: 
                if (adminLogin()) {
                    do {
                        printf("\n--- Admin Menu ---\n");
                        printf("1. Add Candidates\n");
                        printf("2. Remove Candidate\n");
                        printf("3. Show Results\n");
                        printf("4. Declare Winner\n");
                        printf("5. Reset System\n");
                        printf("6. Back to Role Selection\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);

                        switch (adminChoice) {
                            case 1:
                                addCandidates();
                                break;
                            case 2:
                                removeCandidate();
                                break;
                            case 3:
                                calculateResults();
                                break;
                            case 4:
                                declareWinner();
                                break;
                            case 5:
                                resetSystem();
                                break;
                            case 6:
                                printf("Returning to role selection...\n");
                                break;
                            default:
                                printf("Invalid choice! Please try again.\n");
                        }
                    } while (adminChoice != 6);
                }
                break;

            case 2: 
                castVote();
                break;

            case 3:
                printf("Exiting the system. Thank you for participating!\n");
                break;

            default:
                printf("Invalid role! Please choose again.\n");
        }
    } while (role != 3);

    return 0;
}

