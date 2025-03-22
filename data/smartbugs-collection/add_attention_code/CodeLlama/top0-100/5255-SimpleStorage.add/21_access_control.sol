 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
    }

}
