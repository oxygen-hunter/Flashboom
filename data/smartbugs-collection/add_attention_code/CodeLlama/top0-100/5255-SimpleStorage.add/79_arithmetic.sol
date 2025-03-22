 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
