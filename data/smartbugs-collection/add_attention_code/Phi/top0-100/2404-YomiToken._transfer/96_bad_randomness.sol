 

pragma solidity ^0.4.25;

 
contract RandomNumberGenerator {
   
  uint256 private salt =  block.timestamp;

  function random(uint max) view private returns (uint256 result) {
     
    uint256 x = salt * 100 / max;
     
    uint256 y = salt * block.number / (salt % 5);
     
    uint256 seed = block.number / 3 + (salt % 300) + y;
     
    uint256 h = uint256(blockhash(seed));
     
    return uint256((h / x)) % max + 1;
  }
}

library SafeMath {
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256) {
        uint256 c = a + b;
        assert(c >= a && c >= b);
        return c;
    }
}

contract YomiToken {
    using SafeMath for uint256;

    uint256 constant public teamReserve = 100000000e18;
    uint256 constant public foundationReserve = 200000000e18;
    uint256 public lockReleaseDate6Month;
    uint256 public lockReleaseDate1Year;
    address public teamAddr;
    address public foundationAddr;
    mapping (address => uint256) balances;
    mapping (address => bool) public frozenAccounts;
    
    event Transfer(address indexed _from, address indexed _to, uint256 _value);
    
    function _transfer(address _from, address _to, uint256 _value) internal {
        require(_to != 0x0);
        
        if (_from == teamAddr && now < lockReleaseDate6Month) {
            require(balances[_from].sub(_value) >= teamReserve);
        }
        
        if (_from == foundationAddr && now < lockReleaseDate1Year) {
            require(balances[_from].sub(_value) >= foundationReserve);
        }
        
        require(balances[_from] >= _value);
        require(balances[_to] + _value > balances[_to]);
        require(!frozenAccounts[_from]);
        require(!frozenAccounts[_to]);

        uint256 previousBalances = balances[_from].add(balances[_to]);
        balances[_from] = balances[_from].sub(_value);
        balances[_to] = balances[_to].add(_value);
        emit Transfer(_from, _to, _value);
        assert(balances[_from] + balances[_to] == previousBalances);
    }
}
