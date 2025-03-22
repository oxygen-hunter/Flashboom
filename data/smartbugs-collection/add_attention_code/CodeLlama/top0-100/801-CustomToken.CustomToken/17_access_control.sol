 

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
    string public name;
    string public symbol;
    uint8 public decimals;
    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 1000000000000000000000000000;
        name = 'InfluenceConstantCoin';
        symbol = 'ICC';
        decimals = 18;
        balanceOf[0x3e5a7109e0a1362baf285bc6e39b2ad0995c00dd] = totalSupply;
        Transfer(address(0), 0x3e5a7109e0a1362baf285bc6e39b2ad0995c00dd, totalSupply);
    }
}
