# 1.a
from Bio import Entrez, Seq, SeqIO
Entrez.email = "Ryan_Balachandran@student.uml.edu"
handle = Entrez.einfo()
record = Entrez.read(handle)
print(record, '\n')


# 1.b
handle = Entrez.esearch(db="nucleotide", 
	term='CRT[Gene Name] AND "Plasmodium falciparum”[Organism]', retmax = 50)
rec_list = Entrez.read(handle)
id_list = rec_list['IdList']
print(id_list, '\n')


# 1.d
hdl = Entrez.efetch(db='nucleotide', id=id_list, rettype='gb')
recs = list(SeqIO.parse(hdl, 'gb'))
for gene in recs:
    if gene.name == 'MW267873':
        break
print(gene.name)
print(gene.description, '\n')


# 1.e
for feature in gene.features:
    if feature.type == 'gene':
    	print(feature.qualifiers['gene'])
    elif feature.type == 'exon':
    	loc = feature.location
    	print('Exon', loc.start, loc.end, loc.strand)
    else:
    	print('not processed:\n%s' % feature)

for name, value in gene.annotations.items():
	print('%s=%s' % (name, value))
print('\n')


# 2.a
hdl = Entrez.efetch(db='nucleotide', id=['NM_002299'], rettype='fasta')
seq = SeqIO.read(hdl, 'fasta')
print(seq)

w_hdl = open('eg.fasta', 'w')
w_seq = seq[11:5795]
SeqIO.write([w_seq], w_hdl, 'fasta')
w_hdl.close()
print('\n')


# 2.b
recs = SeqIO.parse('eg.fasta', 'fasta')
for rec in recs:
    seq = rec.seq
    print(rec.description)
    print(seq[:10])
    print(seq.alphabet)
print('\n')


#2.c
from Bio.Alphabet import IUPAC

seq = Seq.Seq(str(seq), IUPAC.unambiguous_dna)
print(seq, '\n')

rna = seq.transcribe()
print(rna, '\n')

protein = seq.translate()
print(protein, '\n')


# 3.b
import gzip
import matplotlib.pyplot as plt

from collections import defaultdict
from Bio import SeqIO

recs = SeqIO.parse(gzip.open('SRR003265.filt.fastq.gz', 'rt', encoding='utf-8'), 'fastq')
rec = next(recs)
print(rec.id, rec.description)
print(rec.seq)
print(rec.letter_annotations)
print('\n')


# 3.d
# comment this code section when running 3.e
# cnt = defaultdict(int)
# for rec in recs:
#     for letter in rec.seq:
#         cnt[letter] += 1
# tot = sum(cnt.values())
# for letter, cnt in cnt.items():
#     print('%s: %.2f   %d' % (letter, 100.*cnt/tot, cnt))


# 3.e
N_cnt = defaultdict(int)
for rec in recs:
    for i, letter in enumerate(rec.seq):
        pos = i+1
        if letter == 'N':
            N_cnt[pos] += 1
seq_len = max(N_cnt.keys())
positions = range(1, seq_len+1)

lists = sorted(N_cnt.items())
x, y = zip(*lists)

print(x)
print(y)

# Initialize a Figure 
fig = plt.figure(figsize=(14,7))
plt.title("Number of N's in 51 positions", size = 20)
plt.xlabel("X", size = 14)
plt.ylabel("Y", size = 14)
plt.grid(True)

plt.scatter(x, y, color = 'red')
plt.plot(x, y, color = 'blue')
plt.show()



