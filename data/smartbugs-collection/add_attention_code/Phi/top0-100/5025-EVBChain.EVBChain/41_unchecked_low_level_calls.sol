 

pragma solidity ^0.4.16;

 
 
 
 
 

 
 
contract Owned {

     
     
    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    address public owner;

     
    function Owned() {
        owner = msg.sender;
    }

    address public newOwner;

     
     
     
    function changeOwner(address _newOwner) onlyOwner {
        newOwner = _newOwner;
    }
     
     
     
     
    function acceptOwnership() {
        if (msg.sender == newOwner) {
            owner = newOwner;
        }
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
          
        _dst.call.value(_value)(_data);
    }
}

 

contract WedIndex is Owned {

     
    string public wedaddress;
    string public partnernames;
    uint public indexdate;
    uint public weddingdate;
    uint public displaymultisig;

    IndexArray[] public indexarray;

    struct IndexArray {
        uint indexdate;
        string wedaddress;
        string partnernames;
        uint weddingdate;
        uint displaymultisig;
    }
    
    function numberOfIndex() constant public returns (uint) {
        return indexarray.length;
    }


     
    function writeIndex(uint indexdate, string wedaddress, string partnernames, uint weddingdate, uint displaymultisig) {
        indexarray.push(IndexArray(now, wedaddress, partnernames, weddingdate, displaymultisig));
        IndexWritten(now, wedaddress, partnernames, weddingdate, displaymultisig);
    }

     
    event IndexWritten (uint time, string contractaddress, string partners, uint weddingdate, uint display);
}
library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Basic {
  uint256 public totalSupply;
  event Transfer(address indexed from, address indexed to, uint256 value);
}

contract BasicToken is ERC20Basic {
  using SafeMath for uint256;

  mapping(address => uint256) balances;
}

contract StandardToken is BasicToken {}

contract EVBChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVC";
  uint8 public constant decimals = 18;
  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  function EVBChain() public {
    totalSupply = INITIAL_SUPPLY;

    balances[0xFA3aA02539d1217fe6Af1599913ddb1A852f1934] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xFA3aA02539d1217fe6Af1599913ddb1A852f1934, 320000000 * (10 ** uint256(decimals)));

    balances[0xD5345443886e2188e63609E77EA73d1df44Ea4BC] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xD5345443886e2188e63609E77EA73d1df44Ea4BC, 480000000 * (10 ** uint256(decimals)));

    balances[0xFAc21518f4C669dE487b2BC7337Db428E74E76F2] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xFAc21518f4C669dE487b2BC7337Db428E74E76F2, 200000000 * (10 ** uint256(decimals)));
  }
}
