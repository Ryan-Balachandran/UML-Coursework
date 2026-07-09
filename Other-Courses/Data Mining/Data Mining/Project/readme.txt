Name: Ryan Balachandran
Description of implementations:

I HAVE NO RESULTS TO REPORT AS MY PROJECT IS UNFINISHED

1. Imported libraries
2. Read the dataset
3. Examined the data
4. Preprocessed the data with one-hot binary code
5. Split the dataset into training, testing, and validation
6. Write the split dataset into their respective files

7. Formulas

Sigmoid function was simple:
	s = 1/(1+np.exp(-x))
	return s

inverse_sigmoid:
	s = sig(x)
	ds = s*(1-s)
	return ds

Error:
	sum_square_error = 0.0
	for i in range(len(t)):
		sum_square_error += 0.5*(o[i] - t[i])**2.0
		mean_square_error = sum_square_error / len(o)
	return mean_square_error

inverse_error:
	return (t[i] - o[i])

8. Models

Evaluation:

I had a lot of problems here. First, it was very difficult to understand what the professor was doing with the code.

I had a lot of trouble with the evaluation function but I know I need to evaluate the sigmoid of the 1st input values and the weight, then the sigmoid of the 1st layer and the weight.

I had help from varsity tutors, but we still had a tough time.

Backprop:
	weight_delta = inv_error * inv_sig        
	weight = self.weight - self.weight_delta * LEARNING_RATE
	bias += LEARNING_RATE * weight_delta    #?
        
	self.weight += LEARNING_RATE * weight
	self.weight_delta += LEARNING_RATE * weight_delta

	return weights, bias    

In the main function of the program, I did not exactly what I needed to do for setting up the first and second layer, then evaluating it. This also gave us troubles with the evaluating function. 

When run currently as it is, it returns an error for dimensions not being the same. I believe I have to transpose something in evaluation or backdrop but I don't know what.

9. At the time, I am most familiar with doing python in Jupiter notebook. All you need to do to run it is start at the first cell and press shift+enter, or go to Cell drop down box at the top, and select run all.

I probably should have done this in separate files, but it would have caused me more trouble. As it is, the project is incomplete but almost done. As far as I know I just needed to get the evaluation function to work and fix the dimension error.

It would have been very helpful for the professor to have gone over the project instead of just showing us some slides on what to do.    


