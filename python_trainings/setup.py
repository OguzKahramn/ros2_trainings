from setuptools import setup

package_name = 'python_trainings'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='oguzk',
    maintainer_email='oguzkahraman16@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "range_pub = python_trainings.range_sensor_pub:main",
            "range_sub = python_trainings.range_sensor_sub:main", 
        ],
    },
)
