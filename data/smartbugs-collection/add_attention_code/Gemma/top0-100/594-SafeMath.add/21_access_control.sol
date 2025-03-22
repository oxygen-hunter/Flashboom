 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;



    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
    }

}
