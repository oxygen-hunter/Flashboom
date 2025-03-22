 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    

    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
    }
}