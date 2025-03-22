 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowAdd {
    uint public count = 1;


    
    event Buy(address indexed beneficiary, uint256 payedEther, uint256 tokenAmount);
    
    function test(string nothing) public returns(string hello) {
        emit Buy(msg.sender, now, now + 36000);
        hello = nothing;
    }

    function run(uint256 input) public {
         
        count += input;
    }
}
