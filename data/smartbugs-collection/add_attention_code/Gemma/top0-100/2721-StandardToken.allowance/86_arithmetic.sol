 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowSingleTransaction {
    uint public count = 1;

     
    function overflowaddtostate(uint256 input) public {
         
        count += input;
    }

     
    function overflowmultostate(uint256 input) public {
         
        count *= input;
    }

     
    function underflowtostate(uint256 input) public {
         
        count -= input;
    }

     
    function overflowlocalonly(uint256 input) public {
         
        uint res = count + input;
    }

     
    function overflowmulocalonly(uint256 input) public {
         
        uint res = count * input;
    }

     
    function underflowlocalonly(uint256 input) public {
         
       	uint res = count - input;
    }

}

/**
 * @dev Function to check the amount of tokens that an owner allowed to a spender.
 * @param _owner address The address which owns the funds.
 * @param _spender address The address which will spend the funds.
 * @return A uint256 specifying the amount of tokens still available for the spender.
 */
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
