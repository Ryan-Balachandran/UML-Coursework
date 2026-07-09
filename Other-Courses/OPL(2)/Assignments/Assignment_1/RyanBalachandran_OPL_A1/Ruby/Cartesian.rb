# Ruby program of Cartesian product

p [1, 2].product([3, 4])    # Take the product of two arrays: [1, 2] and [3, 4] to produce the cartesian product between them
p [3, 4].product([1, 2])    # Take the product of two arrays: [3, 4] and [1, 2] to produce the cartesian product between them
p [1, 2].product([])        # Take the product of two arrays: [1, 2] and [] to produce the empty set
p [].product([1, 2])        # Take the product of two arrays: [] and [1, 2] to produce the empty set
p [3, 4].product([])        # Take the product of two arrays: [3, 4] and [] to produce the empty set
p [].product([3, 4])        # Take the product of two arrays: [] and [3, 4] to produce the empty set
p ['a', 'b', 'c'].product([1, 2])       #
p ["dog", "cat", "bird"].product(["bark", "meow", "chirp"])     #
