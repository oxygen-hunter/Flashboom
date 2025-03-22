 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
    }

}
