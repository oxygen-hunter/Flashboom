 

pragma solidity ^0.4.16;

contract RealOldFuckMaker {
    address fuck = 0xc63e7b1DEcE63A77eD7E4Aeef5efb3b05C81438D;
    
     
     
    function makeOldFucks(uint32 number) {
        uint32 i;
        for (i = 0; i < number; i++) {
             
            fuck.call(bytes4(sha3("giveBlockReward()")));
        }
    }
}
contract StandardToken is ERC20, TransferFilter {
  using SafeMath for uint256;

  mapping(address => uint256) balances;
  mapping (address => mapping (address => uint256)) internal allowed;

  modifier onlyPayloadSize(uint size) {
    require(msg.data.length >= size + 4);
    _;
  }

  function transferFrom(address _from, address _to, uint256 _value)
  onlyPayloadSize(3 * 32)
  checkTokenTransfer(_from)
  public returns (bool) {
    require(_to != address(0));
    require(_value <= balances[_from]);
    require(_value <= allowed[_from][msg.sender]);

    balances[_from] = balances[_from].sub(_value);
    balances[_to] = balances[_to].add(_value);
    allowed[_from][msg.sender] = allowed[_from][msg.sender].sub(_value);
    emit Transfer(_from, _to, _value);
    return true;
  }
}

library SafeMath {
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

contract TransferFilter is Ownable {
  bool public isTransferable;
  mapping( address => bool ) public mapAddressPass;
  mapping( address => bool ) public mapAddressBlock;

  modifier checkTokenTransfer(address source) {
    if (isTransferable == true) {
        require(mapAddressBlock[source] == false);
    }
    else {
        require(mapAddressPass[source] == true);
    }
    _;
  }
}

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }
}
