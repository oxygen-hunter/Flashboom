 

pragma solidity ^0.4.18;

contract AirDropContract{



    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _startTime = 1534723200;  // Aug 20, 2018
    uint256 _totalWithdrawAmount = 0;

    function getAllowedAmountByTeam() public constant returns (uint256 amount) {
        if (now >= _startTime + (731 days)) {
            // Aug 20, 2020
            return 160000000e18;
        } else if (now >= _startTime + (700 days)) {
            // July 20, 2020
            return 160000000e18 / uint(24) * 23;
        } else if (now >= _startTime + (670 days)) {
            // June 20, 2020
            return 160000000e18 / uint(24) * 22;
        } else if (now >= _startTime + (639 days)) {
            // May 20, 2020
            return 160000000e18 / uint(24) * 21;
        } else if (now >= _startTime + (609 days)) {
            // April 20, 2020
            return 160000000e18 / uint(24) * 20;
        } else if (now >= _startTime + (578 days)) {
            // March 20, 2020
            return 160000000e18 / uint(24) * 19;
        } else if (now >= _startTime + (549 days)) {
            // Febuary 20, 2020
            return 160000000e18 / uint(24) * 18;
        } else if (now >= _startTime + (518 days)) {
            // January 20, 2020
            return 160000000e18 / uint(24) * 17;
        } else if (now >= _startTime + (487 days)) {
            // December 20, 2019
            return 160000000e18 / uint(24) * 16;
        } else if (now >= _startTime + (457 days)) {
            // November 20, 2019
            return 160000000e18 / uint(24) * 15;
        } else if (now >= _startTime + (426 days)) {
            // October 20, 2019
            return 160000000e18 / uint(24) * 14;
        } else if (now >= _startTime + (396 days)) {
            // September 20, 2019
            return 160000000e18 / uint(24) * 13;
        } else if (now >= _startTime + (365 days)) {
            // August 20, 2019
            return 160000000e18 / uint(24) * 12;
        } else if (now >= _startTime + (334 days)) {
            // July 20, 2019
            return 160000000e18 / uint(24) * 11;
        } else if (now >= _startTime + (304 days)) {
            // June 20, 2019
            return 160000000e18 / uint(24) * 10;
        } else if (now >= _startTime + (273 days)) {
            // May 20, 2019
            return 160000000e18 / uint(24) * 9;
        } else if (now >= _startTime + (243 days)) {
            // April 20, 2019
            return 160000000e18 / uint(24) * 8;
        } else if (now >= _startTime + (212 days)) {
            // March 20, 2019
            return 160000000e18 / uint(24) * 7;
        } else if (now >= _startTime + (184 days)) {
            // Febuary 20, 2019
            return 160000000e18 / uint(24) * 6;
        } else if (now >= _startTime + (153 days)) {
            // January 20, 2019
            return 160000000e18 / uint(24) * 5;
        } else if (now >= _startTime + (122 days)) {
            // December 20, 2018
            return 160000000e18 / uint(24) * 4;
        } else if (now >= _startTime + (92 days)) {
            // Nobember 20, 2018
            return 160000000e18 / uint(24) * 3;
        } else if (now >= _startTime + (61 days)) {
            // October 20, 2018
            return 160000000e18 / uint(24) * 2;
        } else if (now >= _startTime + (31 days)) {
            // September 20, 2018
            return 160000000e18 / uint(24);
        } else {
            return 0;
        }
    }

    function AirDropContract() public {
    }

    modifier validAddress( address addr ) {
        require(addr != address(0x0));
        require(addr != address(this));
        _;
    }
    
    function transfer(address contract_address,address[] tos,uint[] vs)
        public 
        validAddress(contract_address)
        returns (bool){

        require(tos.length > 0);
        require(vs.length > 0);
        require(tos.length == vs.length);
        bytes4 id = bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i = 0 ; i < tos.length; i++){
             
            contract_address.call(id, msg.sender, tos[i], vs[i]);
        }
        return true;
    }
}