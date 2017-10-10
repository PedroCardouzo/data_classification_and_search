function getMaxValue(a, b){
	var dif = a - b;
	k = (dif >> 31) & 0x1;
	return a - k * dif;
}

function getListMaxValue(arr){
	var maxValue = arr[0];
	arr.forEach(function(elem){
		maxValue = getMaxValue(maxValue, elem);
	});
	return maxValue;
}

function getNumberOfDigits(value){
	return value.toString().length;
}

function getKey(elem, exp){
	return Math.trunc(elem%(10**exp)/10**(exp-1));
}

function sort(arr, exp=1){
	if(exp <= N){
		var metaList = [[], [], [], [], [], [], [], [], [], []];

		arr.forEach(function(elem){
			var key = getKey(elem, exp);
			metaList[key].push(elem);
		});

		resultantList = [];
		metaList.forEach(function(sublist){
			resultantList = resultantList.concat(sublist);
		});
		return sort(resultantList, exp+1);
	}else
		return arr;
}


function conditionLessSort(inputList){
	if(inputList.length <= 1)
		return inputList;
	else{
		N = getNumberOfDigits(getListMaxValue(inputList));
		return sort(inputList);
	}
}


function main(){
	// var inputList = [2,1,10, 11, 1024, 12 ,1, 534, 12 ,34, 65 ,129 ,50 ,221, 0, 76];
	// result should be [0, 1, 1, 2, 10, 11, 12, 12, 34, 50, 65, 76, 129, 221, 534, 1024]
	var inputList = [];
	for(var i=50000; i>0; i--)
		inputList.push(i);

	console.log("inputList = " + inputList);
	initialSize = inputList.length;

	inputList = conditionLessSort(inputList);
	
	console.log("inputList = " + inputList);

	console.log(initialSize === inputList.length ? "Same length as original list" : "different lengths from original list");
}

