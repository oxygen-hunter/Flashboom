 

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
