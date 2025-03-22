 

pragma solidity ^0.4.24;


contract B {
    address public owner = msg.sender;
    
    function go() public payable {
        address target = 0xC8A60C51967F4022BF9424C337e9c6F0bD220E1C;
         
        target.call.value(msg.value)();
        owner.transfer(address(this).balance);
    }
    
    function() public payable {
    }
}
library SafeMath {

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract DetailedERC20 {
  string public name;
  string public symbol;
  uint8 public decimals;

  function DetailedERC20(string _name, string _symbol, uint8 _decimals) public {
    name = _name;
    symbol = _symbol;
    decimals = _decimals;
  }
}

contract BasicToken {
  using SafeMath for uint256;

  mapping(address => uint256) balances;

  uint256 totalSupply_;

}

contract CustomToken is BasicToken, DetailedERC20 {

    function CustomToken(string _name, string _symbol, uint8 _decimals, uint maximumSupply) DetailedERC20(_name, _symbol, _decimals) {

        totalSupply_ = totalSupply_.add(maximumSupply * (10 ** uint(decimals)));
        balances[msg.sender] = balances[msg.sender].add(totalSupply_);
    }

}
