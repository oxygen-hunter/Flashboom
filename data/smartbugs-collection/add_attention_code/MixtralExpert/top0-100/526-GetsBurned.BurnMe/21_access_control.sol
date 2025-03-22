 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;



    function BurnMe () {
        selfdestruct(address(this));
    }

    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
    }

}
