 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    

    
    event Buy(address indexed beneficiary, uint256 payedEther, uint256 tokenAmount);
    
    function test(string nothing) public returns(string hello) {
        emit Buy(msg.sender, now, now + 36000);
        hello = nothing;
    }

    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
    }
}