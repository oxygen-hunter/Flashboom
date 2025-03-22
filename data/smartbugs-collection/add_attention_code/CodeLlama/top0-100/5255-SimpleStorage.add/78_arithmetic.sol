 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function run(uint256 input) public {
         
        count *= input;
    }
}
