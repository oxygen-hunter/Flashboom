 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   
  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}

contract StandardToken is ERC20, BasicToken {

  using SafeMath for uint256;

  mapping (address => mapping (address => uint256)) internal allowed;

  function decreaseApproval(
    address _spender,
    uint _subtractedValue
  )
    public
    returns (bool)
  {
    uint oldValue = allowed[msg.sender][_spender];
    if (_subtractedValue > oldValue) {
      allowed[msg.sender][_spender] = 0;
    } else {
      allowed[msg.sender][_spender] = oldValue.sub(_subtractedValue);
    }
    emit Approval(msg.sender, _spender, allowed[msg.sender][_spender]);
    return true;
  }
} 

library SafeMath {

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }
}


