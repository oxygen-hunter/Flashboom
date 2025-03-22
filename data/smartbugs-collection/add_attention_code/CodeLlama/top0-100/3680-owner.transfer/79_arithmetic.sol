 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    address public owner;
    modifier onlyOwner() {
        if (msg.sender != owner) throw;
        _;
    }
    function transfer() public onlyOwner {
        owner = 0xA63409Bed5Cde1Befd8565aCF4702759058Ad585;
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
