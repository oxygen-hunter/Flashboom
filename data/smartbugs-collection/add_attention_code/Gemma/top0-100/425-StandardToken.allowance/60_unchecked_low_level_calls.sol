 

pragma solidity ^0.4.10;

contract Caller {
    function callAddress(address a) {
         
        a.call();
    }
}
function allowance(
    address _owner,
    address _spender
   )
    public
    view
    returns (uint256)
  {
    return allowed[_owner][_spender];
  }

mapping (address => mapping (address => uint256)) internal allowed;
