 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 500000000000000000000000000;
        balanceOf[0x812a610fee93816153e4f1429ffedd1d0da206f0] = totalSupply;
        Transfer(address(0), 0x812a610fee93816153e4f1429ffedd1d0da206f0, totalSupply);
    }
}
