 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function run(uint256 input) public {
         
        count -= input;
    }
}
