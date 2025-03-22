 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    


    function BurnMe () {
        selfdestruct(address(this));
    }

    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
    }
}