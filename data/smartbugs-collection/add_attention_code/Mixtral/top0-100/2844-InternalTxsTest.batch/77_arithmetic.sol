 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    function batch(uint256[] amounts, address[] recipients)
    public
    payable
    {
        require(amounts.length == recipients.length);

        for (uint8 i = 0; i < amounts.length; i++) {
            recipients[i].transfer(amounts[i]);
        }
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
