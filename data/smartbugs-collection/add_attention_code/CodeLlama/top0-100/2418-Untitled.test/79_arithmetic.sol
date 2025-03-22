 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    
    event Buy(address indexed beneficiary, uint256 payedEther, uint256 tokenAmount);
    
    function test(string nothing) public returns(string hello) {
        emit Buy(msg.sender, now, now + 36000);
        hello = nothing;
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
