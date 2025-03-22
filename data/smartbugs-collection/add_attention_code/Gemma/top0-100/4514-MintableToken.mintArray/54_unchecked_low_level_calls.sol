 

pragma solidity ^0.4.24;
 
contract demo{
    
    function transfer(address from,address caddress,address[] _tos,uint v)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v);
        }
        return true;
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
