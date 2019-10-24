from random import choice
import sys

def select_indice(seq):
    """
    Randomly select an element from a sequence and removes it
    """
    picked_indice = choice(list(seq))
    seq.remove(picked_indice)
    return picked_indice

# get the number of cards
num_cards = int(input())
# not yet flipped cards indices
not_flipped_indices = {i for i in range(1, 2*num_cards + 1)}
# map each card N to the indice where it was found
cards_indices = dict()
# a list of pendent known matches
known_matches = list()
# while there are cards in game
while not_flipped_indices or known_matches:
    # look for any pendent known matches
    if known_matches:
        i1, i2 = known_matches.pop()
    else:
        # randomly pick two indices
        i1 = select_indice(not_flipped_indices)
        i2 = select_indice(not_flipped_indices)
    # send them to the interactor
    print(f"{i1} {i2}")
    # read the response
    response = input()
    # handle failure
    if response == -1:
        exit(1)
    elif response != "MATCH":
        # it's not a match, but a card number
        card1, card2 = response.split(' ')
        card1 = int(card1)
        card2 = int(card2)
        # save the cards in our structure
        if card1 not in cards_indices:
            cards_indices[card1] = [i1]
        else:
            # at this point, we know both locations for card1
            cards_indices[card1].append(i1)
            # add known match to the queue
            known_matches.append(cards_indices[card1])
        
        if card2 not in cards_indices:
            cards_indices[card2] = [i2]
        else:
            # at this point, we know both locations for card1
            cards_indices[card2].append(i2)
            # add known match to the queue
            known_matches.append(cards_indices[card2])
    #print(not_flipped_indices, file=sys.stderr)
print("-1")