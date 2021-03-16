from setuptools import setup, find_packages

setup(
    name='sdrx',
    version='0.1.0',
    description='Python bindings for ION GNSS Metadata Standard',
    author='''Cillian O'Driscoll''',
    author_email='cillian@codc.ie',
    packages=find_packages(),
    package_data={'sdrx': ["*.so"]},
    include_package_data=True,
    zip_safe=False,
)
