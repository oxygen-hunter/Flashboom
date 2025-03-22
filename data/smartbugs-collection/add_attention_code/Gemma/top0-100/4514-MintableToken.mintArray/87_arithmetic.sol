 

 pragma solidity ^0.4.18;

 contract Token {

   mapping(address => uint) balances;
   uint public totalSupply;

   function Token(uint _initialSupply) {
     balances[msg.sender] = totalSupply = _initialSupply;
   }

   function transfer(address _to, uint _value) public returns (bool) {
      
     require(balances[msg.sender] - _value >= 0);
      
     balances[msg.sender] -= _value;
     balances[_to] += _value;
     return true;
   }

   function balanceOf(address _owner) public constant returns (uint balance) {
     return balances[_owner];
   }
 }

library SafeMath {
  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
    c = a + b;
    assert(c >= a);
    return c;
  }
}

contract MintableToken {
  using SafeMath for uint256;
  
  mapping(address => uint256) balances;
  uint256 totalSupply_;
  uint256 public maxMintQuantity;
  
  event Mint(address indexed to, uint256 amount);
  event Transfer(address indexed from, address indexed to, uint256 value);

  function mint(address _to, uint256 _amount) public returns (bool) {
    require(maxMintQuantity >= totalSupply_.add(_amount));

    totalSupply_ = totalSupply_.add(_amount);
    balances[_to] = balances[_to].add(_amount);
    emit Mint(_to, _amount);
    emit Transfer(address(0), _to, _amount);
    return true;
  }

  function mintArray(address[] _to, uint256[] _value) public returns (bool) {
    uint cnt = _to.length;
    uint cntVal = _value.length;

    require(cnt > 0);
    require(cnt == cntVal);

    for (uint i = 0; i < cnt; i++) {
      mint(_to[i], _value[i]);
    }

    return true;
  }
}
