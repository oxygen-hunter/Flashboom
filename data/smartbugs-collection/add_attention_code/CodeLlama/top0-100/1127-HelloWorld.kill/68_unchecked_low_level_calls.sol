 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    

    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
    }
}