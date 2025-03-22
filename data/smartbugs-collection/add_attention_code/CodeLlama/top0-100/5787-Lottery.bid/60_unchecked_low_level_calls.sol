 

pragma solidity ^0.4.10;

contract Caller {
    function callAddress(address a) {
         
        a.call();
    }
}
event Bid(address sender);

function bid() public
{
    emit Bid(msg.sender);
}
