{
	'targets': [
		{
			'target_name': 'uvrun2',
			'sources': ['uvrun2.cc'],
			'variables': {
				'node_version_maj': '<!(node --version | sed -e "s/^v\([0-9]*\)\\..*$/\\1/")'
			},
			"conditions": [
				['node_version_maj == "0"', {'defines': ['NODE_0']}],
				['node_version_maj == "4"', {'defines': ['NODE_4']}],
				['node_version_maj == "5"', {'defines': ['NODE_5']}],
				['node_version_maj == "6"', {'defines': ['NODE_6']}],
				['node_version_maj == "7"', {'defines': ['NODE_7']}],
				['node_version_maj == "8"', {'defines': ['NODE_8']}],
				['node_version_maj == "9"', {'defines': ['NODE_9']}],
				['node_version_maj == "10"', {'defines': ['NODE_10']}],
				['node_version_maj == "11"', {'defines': ['NODE_11']}],
				['node_version_maj == "12"', {'defines': ['NODE_12']}],
				['node_version_maj == "13"', {'defines': ['NODE_13']}],
				['node_version_maj == "14"', {'defines': ['NODE_14']}]
			]
		}
	]
}
