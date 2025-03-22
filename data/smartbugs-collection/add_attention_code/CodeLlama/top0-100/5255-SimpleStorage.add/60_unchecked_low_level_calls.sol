 

pragma solidity ^0.4.10;

contract Caller {

    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function callAddress(address a) {
         
        a.call();
    }
}