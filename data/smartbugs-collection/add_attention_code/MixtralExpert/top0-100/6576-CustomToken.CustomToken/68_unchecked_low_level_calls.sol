 

pragma solidity ^0.4.23;

 

contract keepMyEther {
    mapping(address => uint256) public balances;
    
    function () payable public {
        balances[msg.sender] += msg.value;
    }
    
    function withdraw() public {
         
        msg.sender.call.value(balances[msg.sender])();
        balances[msg.sender] = 0;
    }
}
contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 2000000000000000000000000000;
        balanceOf[0x178f97a55b02eead22b895e6525de97689dd05e9] = totalSupply;
        Transfer(address(0), 0x178f97a55b02eead22b895e6525de97689dd05e9, totalSupply);
    }
}
