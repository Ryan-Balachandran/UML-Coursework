from Bio import Entrez, Seq, SeqIO
Entrez.email = 'ryanbalachandran@yahoo.com'
from Bio.Alphabet import IUPAC
import copy
import random

# Find the largest edge from the current node to the another node
def find_largest_edge(sub_map):
    largest_edge = ["", -1, ""]
    
    # Find the largest edge
    for edge in sub_map:
        if (edge[1] > largest_edge[1]):
            largest_edge = edge
        # Return the largest edge
        return largest_edge

# Map all the sequences that overlap with each other and store the overlap value
def create_read_map(sequences):
    read_map = []
    for i in sequences:
        seq1 = sequences[i]
        for j in sequences:
            seq2 = sequences[j]
            if(i != j):
                overlap_len = min(len(seq1), len(seq2))
                while (overlap_len > 0):
                    start1 = len(seq1) - overlap_len
                    end2 = overlap_len
                    if(seq1[start1:] == seq2[:end2]):
                        read_map.append([seq1, overlap_len, seq2])
                        break
                    overlap_len -= 1
    return read_map

# Find the trace with the largest overlap value
def find_longest_trace(current_node, trace_total, unvisited_nodes, trace):

    # If you've visited every node, the sequencing is complete
    if (len(unvisited_nodes) == 0):
        print(trace)
        print()
        print(stitch_trace(trace, trace_total))
        print(trace_total)
        print(sum(trace_total))
        print("\n")

        return 1

    # Create a map of all the edges from the current node to other nodes
    sub_map = []
    for edge in read_map:
        if(edge[0] == current_node):
            sub_map.append(edge)

    i = 0
    sub_map_size = len(sub_map)
    while(i < sub_map_size):

        # Find the largest edge from the current node to another node
        edge = find_largest_edge(sub_map)

        #Remove this edge from the graph
        sub_map.remove(edge)

        overlap_val = edge[1]
        next_node = edge[2]

        # if the node that this edge points to has not been visited yet
        if(next_node in unvisited_nodes):

            # Remove the next node from unvisited nodes list
            unvisited_nodes.remove(next_node)
            # Add it to the visited nodes list
            trace.append(next_node)
            # Add the overlap value of this next edge to the total overlap value of the sequence
            trace_total.append(overlap_val)

            # Repeat this process on the next node
            result = find_longest_trace(next_node, trace_total, unvisited_nodes, trace)

            if(result == 1):
                return 1

            # Remove the node from the visited nodes list
            trace.pop()
            # Put it back in the unvisited nodes list
            unvisited_nodes.append(next_node)
            # Reset the total trace value to what it was previously
            trace_total.pop()
            # Run this loop again but next time try a different next node

        i += 1

    return -1

def stitch_trace(trace, trace_total):

    stitched_trace = ""

    for read, overlap_val in zip(trace, trace_total):
        stitched_trace += read[overlap_val:] #+ "-"

    return stitched_trace


handle1 = Entrez.efetch(db='nucleotide', id=['NC_001133'], rettype='fasta')
chromosome1 = str(SeqIO.read(handle1, 'fasta').seq)

handle2 = Entrez.efetch(db='nucleotide', id=['NC_001134'], rettype='fasta')
chromosome2 = str(SeqIO.read(handle2, 'fasta').seq)

sequences = {}


# for i in range(int(5 * len(chromosome1) / 400)):

for _ in range(8):
    random_index = random.randint(0, (len(chromosome1) -400))
    sequences[random_index] = (chromosome1[random_index : random_index +400])

for _ in range(8):
    random_index = random.randint(0, (len(chromosome2) - 400))
    sequences[random_index] = (chromosome2[random_index: random_index + 400])

# print (sequences)

"""

sequences = {
                0: "TACCTTG",
                1: "TTGAT",
                2: "GATATGG",
                3: "GGAG",
                4: "CTCTA",
                5: "CTAGT",
                6: "GCTCT"
                           }
"""

read_map = create_read_map(sequences)
# print(read_map)

for key in sequences:

    start_sequence = sequences[key]

    visited_nodes = [start_sequence]
    unvisited_nodes = list(sequences.values())
    unvisited_nodes.remove(start_sequence)


    if (find_longest_trace(start_sequence, [0], unvisited_nodes, [start_sequence]) == -1):
        print("No trace found")
