 

 
 

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

contract HODL {
    struct HODL {
        uint256 stake;
        bool invalid;
        bool claimed3M;
        bool claimed6M;
        bool claimed9M;
    }
    mapping (address => HODL) public hodlerStakes;
}

contract EthealHodlHelper {
    HODL private hodl = HODL(0x9ab055FD8189A4128F5940F0e1B3F690AFaCd80c);
    
    function getAddress(address[] keys, bool valid, bool invalid) view external returns (address[] hodlers) {
        uint256 i;
        uint256 result = 0;
        uint256 _s = 0;
        bool _v = false;
        bool _a = false;
        bool _b = false;
        bool _c = false;
        address[] memory _hodlers = new address[](keys.length);

        for (i = 0; i < keys.length; i++) {
            (_s, _v, _a, _b, _c) = hodl.hodlerStakes(keys[i]);
            if ((_v && valid) || (!_v && invalid)) {
                _hodlers[result] = keys[i];
                result++;
            }
        }

        hodlers = new address[](result);
        for (i = 0; i < result; i++) {
            hodlers[i] = _hodlers[i];
        }

        return hodlers;
    }
}
