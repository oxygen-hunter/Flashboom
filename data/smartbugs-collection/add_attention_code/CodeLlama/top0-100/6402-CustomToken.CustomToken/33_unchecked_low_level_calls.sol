 

pragma solidity 0.4.25;

contract ReturnValue {

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
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
