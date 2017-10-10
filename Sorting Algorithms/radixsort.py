import math
from collections import defaultdict

def getMaxValue(a, b):
	dif = a - b;
	k = (dif >> 31) & 0x1; # equivalent to dividing dif by 2^31 and then doing a bitwise 'and' with binary value '1' -> k = 1 if a < b, 0 otherwise
	return a - k * dif

def getListMaxValue(arr):
	maxValue = arr[0]
	for elem in arr:
		maxValue = getMaxValue(maxValue, elem)
	return maxValue

def getNumberOfDigits(value):
	return len(str(value))

def getKey(elem, exp):
	return elem%(10**exp)/10**(exp-1);
	
def sort(arr, exp=1):
	if exp <= N:
		metaList = [[] for i in range(0,10)] # create an empty list of lists with 10 slots

		for elem in arr: # separate the elements in buckets
			key = getKey(elem, exp)
			metaList[key].append(elem)

		resultantList = [] # merge the buckets
		for sublist in metaList:
			resultantList += sublist

		return sort(resultantList, exp+1) # do it again

	else: # you have iterated N times already. Just return the array, its done
		return arr


def conditionLessSort(inputList):
	if len(inputList) <= 1:
		return inputList
	else:
		global N
		N = getNumberOfDigits(getListMaxValue(inputList))
		return sort(inputList)


def main():
	inputList = [2,1,10, 11, 1024, 12 ,1, 534, 12 ,34, 65 ,129 ,50 ,221, 0, 76]
	# result should be [0, 1, 1, 2, 10, 11, 12, 12, 34, 50, 65, 76, 129, 221, 534, 1024]
	# inputList = [i for i in range(0,50000)]
	
	initialSize = len(inputList)

	inputList = conditionLessSort(inputList)
	print(inputList)

	print("Same length as original list" if len(inputList)==initialSize else "different lengths from original list")
	 
if __name__ == "__main__":
	main()





# import math
# from collections import defaultdict

# inputList = [2,1,10, 11, 12 ,1, 534, 12 ,34, 65 ,129 ,50 ,221]


# def getMaxValue(a, b):
# 	c = a - b;
# 	k = (c >> 31) & 0x1;
# 	max = a - k * c;
# 	return max;

# def getListMaxValue(arr):
# 	maxValue = arr[0]
# 	for elem in arr:
# 		maxValue = getMaxValue(maxValue, elem)
# 	return maxValue

# def getMaxDigitNumber(value):
# 	return len(str(value))+1

# def getKey(elem, exp):
# 	return elem%(10**exp)/10**(exp-1);
	
# def sort(arr, exp=1):
# 	if exp <= N:
# 		metaList = [[] for i in range(0,10)]
# 		for subList in arr:
# 			for elem in subList:
# 				key = getKey(elem, exp)
# 				metaList[key].append(elem)

# 		return sort(metaList, exp+1)

# 	else:
# 		return arr


# def conditionLessSort(inputList):
# 	if len(inputList) <= 1:
# 		return inputList
# 	else:
# 		global N
# 		N = getMaxDigitNumber(getListMaxValue(inputList))
# 		arr = []
# 		arr.append(inputList)
# 		result = sort(arr)
# 		return result[0]


# print(conditionLessSort(inputList))

